# distutils: language = c++
# distutils: sources = func_connect.cpp
# distutils: extra_compile_args = -fopenmp
# distutils: extra_link_args= -fopenmp
#cython: language_level=3, boundscheck=False, wraparound=False, initializedcheck=False, cdivision=True
#!/usr/bin/env cython
#-*- coding:utf-8 -*-

""" Generation tools for NNGT """

import warnings

from cython.parallel import parallel, prange

import numpy as np
import scipy.sparse as ssp
from numpy.random import randint

import nngt
from nngt.lib.errors import InvalidArgument
from .connect_tools import *


__all__ = [
    "_distance_rule",
    "_erdos_renyi",
    "_filter",
    "_fixed_degree",
    "_gaussian_degree",
    "_newman_watts",
    "_no_self_loops",
    "_price_scale_free",
    "_random_scale_free",
    "_unique_rows",
]


cdef int MAXTESTS = 1000 # ensure that generation will finish
cdef float EPS = 0.00001

# We now need to fix a datatype for our arrays. I've used the variable
# DTYPE for this, which is assigned to the usual NumPy runtime
# type info object.
DTYPE = np.uint


#-----------------------------------------------------------------------------#
# Simple tools
#------------------------
#

cdef size_t _unique_1d(np.ndarray[size_t, ndim=1] arr):
    cdef np.ndarray[size_t, ndim=1] b = np.unique(arr)
    cdef size_t num_unique = b.shape[0]
    arr[:num_unique] = b
    return num_unique

def _unique_rows(arr):
    b = np.ascontiguousarray(arr).view(np.dtype((np.void,
        arr.dtype.itemsize * arr.shape[1])))
    return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])

def _no_self_loops(array):
    return array[array[:,0] != array[:,1],:]

def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,
                            multigraph):
    '''
    Filter the edges: remove self loops and multiple connections if the graph
    is not a multigraph.
    '''
    if b_one_pop:
        ia_edges_tmp = _no_self_loops(ia_edges_tmp)
    num_added = ia_edges_tmp.shape[0]
    ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
    num_ecurrent += num_added
    if not multigraph:
        ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
        num_ecurrent = ia_edges_tmp.shape[0]
        ia_edges[:num_ecurrent,:] = ia_edges_tmp
    return ia_edges, num_ecurrent


#-----------------------------------------------------------------------------#
# Graph model generation
#------------------------
#

#~ def _fixed_degree(size_t [:] source_ids, size_t [:] target_ids,
#~                   size_t degree, degree_type, float reciprocity,
#~                   bool directed, bool multigraph, existing_edges=None):
#~     '''
#~     Returns a 2D array containing the new edges of a fixe-degree graph.
#~     If the graph has already existing edges, tries to generate additional
#~     edges to add a fixed-degree graph "on top" of the existing edges.
#~     To clarify, if node `n` has already a degree `d_n` and the addition of the
#~     fixed-degree graph is possible, this node will end up with a degree
#~     `d_n + degree`.

#~     .. note :
#~         This function returns only the new edges.
#~     '''
#~     np.random.seed()
#~     cdef int num_source = source_ids.shape[0]
#~     cdef int num_target = target_ids.shape[0]
#~     # type of degree
#~     cdef bool b_out = (degree_type == "out")
#~     cdef bool b_total = (degree_type == "total")
#~     # edges
#~     cdef int edges = num_target*degree if degree_type == "out" else num_source*degree
#~     cdef bool b_one_pop = _check_num_edges(
#~         source_ids, target_ids, edges, directed, multigraph)
#~     # existing edges
#~     cdef int existing = 0
#~     if existing_edges is not None:
#~         existing = np.shape(existing_edges)[0]

#~     # array containing the new edges
#~     cdef size_t [:, :] ia_edges = np.zeros((existing+edges, 2), dtype=size_t)
#~     cdef np.ndarray[size_t, ndim=2] ia_edges = np.zeros((existing+edges, 2))
#~     # differenciate source / target
#~     cdef int idx = 0 if b_out else 1
#~     # nodes from which we will pick randomly
#~     cdef size_t [:] variables = source_ids if b_out else target_ids
#~     cdef np.ndarray[size_t, ndim=1] variables = source_ids if b_out else target_ids
#~     cdef int num_var = variables.shape[0]

#~     return ia_edges

cpdef np.ndarray[unsigned long, ndim=2] _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,
                  np.ndarray[size_t, ndim=1] target_ids,
                  size_t degree, degree_type, reciprocity,
                  bool directed, bool multigraph, existing_edges=None):
    np.random.seed()
    cdef size_t num_source = source_ids.shape[0]
    cdef size_t num_target = target_ids.shape[0]
    msd = np.random.randint(0, num_target+1)
    cdef size_t[:] seeds = msd + np.arange(num_target, dtype=DTYPE)
    # type of degree
    b_out = (degree_type == "out")
    b_total = (degree_type == "total")
    # edges
    edges = num_target*degree if degree_type == "out" else num_source*degree
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    
    existing = 0 if existing_edges is None else existing_edges.shape[0]
    cdef np.ndarray[unsigned long, ndim=2] ia_edges = np.zeros((existing+edges, 2), dtype=np.uint)
    if existing:
        ia_edges[:existing,:] = existing_edges
    cdef int idx = 0 if b_out else 1 # differenciate source / target
    cdef vector[size_t] variables = source_ids if b_out else target_ids # nodes picked randomly

    cdef size_t omp = nngt.config["omp"] 
    cdef int i, j, v
    cdef np.ndarray[size_t, ndim=2] edges_i
    cdef int ecurrent
#~     cdef np.ndarray[size_t, ndim=1] variables_i
    cdef vector[size_t] variables_i = np.zeros(degree)
    with nogil, parallel(num_threads=omp):
        for i in prange(num_target, schedule='dynamic'):
            v = target_ids[i]
            variables_i = _gen_edge_complement(seeds[i], variables, v, degree,
                NULL, multigraph)
            for j in range(degree):
                ia_edges[i*degree + j, idx] = v
                ia_edges[i*degree + j, idx-1] = variables_i[j]
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges


def _gaussian_degree(source_ids, target_ids, avg, std, degree_type,
                     reciprocity, directed, multigraph, existing_edges=None):
    ''' Connect nodes with a Gaussian distribution '''
    np.random.seed()
    source_ids = np.array(source_ids).astype(int)
    target_ids = np.array(target_ids).astype(int)
    num_source, num_target = len(source_ids), len(target_ids)
    # type of degree
    b_out = (degree_type == "out")
    b_total = (degree_type == "total")
    # edges
    num_node = num_source if degree_type == "in" else num_target
    lst_deg = np.around(
        np.maximum(np.random.normal(avg, std, num_node), 0.)).astype(int)
    edges = np.sum(lst_deg)
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    
    num_etotal = 0 if existing_edges is None else existing_edges.shape[0]
    ia_edges = np.zeros((num_etotal+edges, 2), dtype=int)
    if num_etotal:
        ia_edges[:num_etotal,:] = existing_edges
    idx = 0 if b_out else 1 # differenciate source / target
    variables = source_idx if b_out else target_ids # nodes picked randomly

    for i,v in enumerate(target_ids):
        degree_i = lst_deg[i]
        edges_i, ecurrent, variables_i = np.zeros((degree_i,2)), 0, []
        if existing_edges is not None:
            with_v = np.where(ia_edge[:,idx] == v)
            variables_i.extend(ia_edge[with_v:int(not idx)])
            ecurrent = len(variables_i)
        rm = np.argwhere(variables == v)[0]
        rm = rm[0] if len(rm) else -1
        var_tmp = ( np.array(variables, copy=True) if rm == -1 else
                    np.concatenate((variables[:rm], variables[rm+1:])) )
        num_var_i = len(var_tmp)
        ia_edges[num_etotal:num_etotal+degree_i, idx] = v
        while len(variables_i) != degree_i:
            var = var_tmp[randint(0, num_var_i, degree_i-ecurrent)]
            variables_i.extend(var)
            if not multigraph:
                variables_i = list(set(variables_i))
            ecurrent = len(variables_i)
        ia_edges[num_etotal:num_etotal+ecurrent, int(not idx)] = variables_i
        num_etotal += ecurrent
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges
    

def _random_scale_free(source_ids, target_ids, in_exp, out_exp, density,
                       edges, avg_deg, reciprocity, directed, multigraph,
                       **kwargs):
    ''' Connect the nodes with power law distributions '''
    np.random.seed()
    source_ids = np.array(source_ids).astype(int)
    target_ids = np.array(target_ids).astype(int)
    num_source, num_target = len(source_ids), len(target_ids)
    edges, pre_recip_edges = _compute_connections(num_source, num_target,
                                density, edges, avg_deg, directed, reciprocity)
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    
    ia_edges = np.zeros((edges,2),dtype=int)
    num_ecurrent, num_test = 0, 0

    # lists containing the in/out-degrees for all nodes
    ia_in_deg = np.random.pareto(in_exp,num_target)+1
    ia_out_deg = np.random.pareto(out_exp,num_source)+1
    sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
    ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,
                                      ia_in_deg)).astype(int)
    ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,
                                       ia_out_deg)).astype(int)
    sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
    while sum_in != pre_recip_edges or sum_out != pre_recip_edges:
        diff_in = sum_in-pre_recip_edges
        diff_out = sum_out-pre_recip_edges
        idx_correct_in = randint(0,num_target,np.abs(diff_in))
        idx_correct_out = randint(0,num_source,np.abs(diff_out))
        ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)
        ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)
        sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
        ia_in_deg[ia_in_deg<0] = 0
        ia_out_deg[ia_out_deg<0] = 0
    # make the edges
    ia_sources = np.repeat(source_ids,ia_out_deg)
    ia_targets = np.repeat(target_ids,ia_in_deg)
    np.random.shuffle(ia_targets)
    ia_edges_tmp = np.array([ia_sources,ia_targets]).T
    ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
                                     b_one_pop, multigraph)
        
    while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
        num_desired = pre_recip_edges-num_ecurrent
        ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]
        ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
        ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
        ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
                                         b_one_pop, multigraph)
        num_test += 1
    
    if directed and reciprocity > 0:
        while num_ecurrent != edges and num_test < MAXTESTS:
            ia_indices = randint(0, pre_recip_edges,
                                           edges-num_ecurrent)
            ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
            num_ecurrent = edges
            if not multigraph:
                ia_edges_tmp = _unique_rows(ia_edges)
                num_ecurrent = ia_edges_tmp.shape[0]
                ia_edges[:num_ecurrent,:] = ia_edges_tmp
            num_test += 1
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges
    

def _erdos_renyi(source_ids, target_ids, density, edges, avg_deg, reciprocity,
                 directed, multigraph, **kwargs):
    '''
    Returns a numpy array of dimension (2,edges) that describes the edge list
    of an Erdos-Renyi graph.
    @todo: perform all the calculations here
    '''
    np.random.seed()
    source_ids = np.array(source_ids).astype(int)
    target_ids = np.array(target_ids).astype(int)
    num_source, num_target = len(source_ids), len(target_ids)
    edges, pre_recip_edges = _compute_connections(num_source, num_target,
                                density, edges, avg_deg, directed, reciprocity)
    
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    
    ia_edges = np.zeros((edges,2), dtype=int)
    num_test, num_ecurrent = 0, 0 # number of tests and current number of edges
    
    while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
        ia_sources = source_ids[randint(0, num_source,
                                        pre_recip_edges-num_ecurrent)]
        ia_targets = target_ids[randint(0, num_target,
                                        pre_recip_edges-num_ecurrent)]
        ia_edges_tmp = np.array([ia_sources,ia_targets]).T
        ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
                                         b_one_pop, multigraph)
        num_test += 1
    
    if directed and reciprocity > 0:
        while num_ecurrent != edges and num_test < MAXTESTS:
            ia_indices = randint(0, pre_recip_edges,
                                           edges-num_ecurrent)
            ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
            num_ecurrent = edges
            if not multigraph:
                ia_edges_tmp = _unique_rows(ia_edges)
                num_ecurrent = ia_edges_tmp.shape[0]
                ia_edges[:num_ecurrent,:] = ia_edges_tmp
            num_test += 1
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges


def _price_scale_free():
    pass


def _circular_graph(node_ids, coord_nb):
    '''
    Connect every node `i` to its `coord_nb` nearest neighbours on a circle
    '''
    nodes = len(node_ids)
    ia_sources, ia_targets = np.zeros(nodes*coord_nb), np.zeros(nodes*coord_nb)
    ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)
    dist = coord_nb/2.
    neg_dist = -int(np.floor(dist))
    pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist
    ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))
    ia_targets = np.tile(ia_base, nodes)+ia_sources
    ia_targets[ia_targets<-0.5] += nodes
    ia_targets[ia_targets>nodes-0.5] -= nodes
    return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T

def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,
                  directed, multigraph, **kwargs):
    '''
    Returns a numpy array of dimension (num_edges,2) that describes the edge 
    list of a Newmaan-Watts graph.
    '''
    np.random.seed()
    node_ids = np.array(source_ids, dtype=int)
    target_ids = np.array(target_ids, dtype=int)
    nodes = len(node_ids)
    circular_edges = nodes*coord_nb
    num_edges = int(circular_edges*(1+proba_shortcut))
    num_edges, circular_edges = (num_edges, circular_edges if directed
                             else (int(num_edges/2), int(circular_edges/2)))
    
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    if not b_one_pop:
        raise InvalidArgument("This graph model can only be used if source \
                              and target populations are the same")
    # generate the initial circular graph
    ia_edges = np.zeros((num_edges,2),dtype=int)
    ia_edges[:circular_edges,:] = _circular_graph(node_ids, coord_nb)
    # add the random connections
    num_test, num_ecurrent = 0, circular_edges
    while num_ecurrent != num_edges and num_test < MAXTESTS:
        ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
        ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
        ia_edges_tmp = np.array([ia_sources,ia_targets]).T
        ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
                                         b_one_pop, multigraph)
        num_test += 1
    ia_edges = _no_self_loops(ia_edges)
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges


def _distance_rule(source_ids, target_ids, density, edges, avg_deg, scale,
                   rule, shape, positions, directed, multigraph, **kwargs):
    '''
    Returns a distance-rule graph
    '''
    np.random.seed()
    def exp_rule(pos_src, pos_target):
        dist = np.linalg.norm(pos_src-pos_target,axis=0)
        return np.exp(np.divide(dist,-scale))
    def lin_rule(pos_src, pos_target):
        dist = np.linalg.norm(pos_src-pos_target,axis=0)
        return np.divide(scale-dist,scale).clip(min=0.)
    dist_test = exp_rule if rule == "exp" else lin_rule
    # compute the required values
    source_ids = np.array(source_ids).astype(int)
    target_ids = np.array(target_ids).astype(int)
    num_source, num_target = len(source_ids), len(target_ids)
    edges, _ = _compute_connections(num_source, num_target,
                             density, edges, avg_deg, directed, reciprocity=-1)
    b_one_pop = _check_num_edges(
        source_ids, target_ids, edges, directed, multigraph)
    # create the edges
    ia_edges = np.zeros((edges,2), dtype=int)
    num_test, num_ecurrent = 0, 0
    while num_ecurrent != edges and num_test < MAXTESTS:
        num_create = edges-num_ecurrent
        ia_sources = source_ids[randint(0, num_source, num_create)]
        ia_targets = target_ids[randint(0, num_target, num_create)]
        test = dist_test(positions[:,ia_sources],positions[:,ia_targets])
        ia_valid = np.greater(test,np.random.uniform(size=num_create))
        ia_edges_tmp = np.array([ia_sources[ia_valid],ia_targets[ia_valid]]).T
        ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
                                         b_one_pop, multigraph)
        num_test += 1
    if num_test == MAXTESTS:
        ia_edges = ia_edges[:num_ecurrent,:]
        warnings.warn("Maximum number of tests reached, stopped  generation \
with {} edges.".format(num_ecurrent), RuntimeWarning)
    if not directed:
        ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
        ia_edges = _unique_rows(ia_edges)
    return ia_edges

def price_network():
    #@todo: do it for other libraries
    pass
