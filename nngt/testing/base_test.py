#!/usr/bin/env python
#-*- coding:utf-8 -*-

# base_test.py

# This file is part of the NNGT module
# Distributed as a free software, in the hope that it will be useful, under the
# terms of the GNU General Public License.

"""
Define the XmlHandler and the TestBasis class for NNGT testing module
"""

# std imports
import sys
import unittest
from abc import ABCMeta, abstractmethod, abstractproperty
from os import listdir
from os.path import abspath, dirname, isfile, join

# third-party library
import numpy as np
import xml.etree.ElementTree as xmlet
from six import add_metaclass

import nngt
from tools_testing import _bool_from_string, _xml_to_dict, _list_from_string



#-----------------------------------------------------------------------------#
# Path to input files
#------------------------
#

# folder containing all networks
test_dir = dirname(abspath(__file__)) + "/"
network_dir = test_dir + "Networks/"

# file containing networks' properties and instructions
xml_file = test_dir + "graph_tests.xml"


#-----------------------------------------------------------------------------#
# XmlResultParser
#------------------------
#

class XmlHandler:

    ''' Class parsing the XML reference files. '''
    
    di_type = {
        "float": float,
        "double": float,
        "string": str,
        "str": str,
        "int": int,
        "bool": _bool_from_string
    }
    
    def __init__(self):
        tree = xmlet.parse(xml_file)
        self.root = tree.getroot()
        self.graphs = self.root.find("graphs")
    
    def result(self, elt):
        return self.di_type[elt.tag](elt.text)
    
    def get_graph_list(self, test):
        elt_test = self.root.find('./test[@name="{}"]'.format(test))
        return [ child.text for child in elt_test.find("graph_list") ]

    def get_graph_options(self, graph):
        graph_elt = self.graphs.find('./graph[@name="{}"]'.format(graph))
        elt_options = None
        for child in graph_elt:
            if child.tag in ("load_options", "generate_options"):
                elt_options = child
        return _xml_to_dict(elt_options, self.di_type)
    
    def get_result(self, graph, result_name):
        elt_test = self.graphs.find('./graph[@name="{}"]'.format(graph))
        elt_result = elt_test.find('./*[@name="{}"]'.format(result_name))
        return self.result(elt_result)


#-----------------------------------------------------------------------------#
# TestBasis class
#------------------------
#

class MetaAbcCompat(ABCMeta, type):
    pass

@add_metaclass(MetaAbcCompat)
class TestBasis(unittest.TestCase):

    '''
    Class defining the graphs and the conditions in which they will be tested.
    
    warning ::
        All test methods should be of the form:
        ``def test_method(self, graph, **kwargs)``
    '''
    
    #-------------------------------------------------------------------------#
    # Class properties
    
    @classmethod
    def setUpClass(cls):
        cls.graphs = []
    
    tolerance = 1e-5
    parser = XmlHandler()
    graphs = []
    instructions = []
    
    #-------------------------------------------------------------------------#
    # Instance
    
    def setUp(self):
        if not self.graphs:
            for graph_name in self.parser.get_graph_list(self.test_name):
                self.graphs.append(graph_name)

    @abstractproperty
    def test_name(self):
        pass
    
    def get_expected_result(self, graph, res_name):
        return self.parser.get_result(graph.get_name(), res_name)

    @abstractmethod
    def gen_graph(self, graph_name):
        '''
        Must return a ``(g, di)`` tuple with `g` the graph instance and `di`
        the generation instructions (as a ``dict``) or ``None``.
        '''
        pass
    
