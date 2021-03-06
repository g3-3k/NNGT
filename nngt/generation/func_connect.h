// connect.h
//
// Accelerated network generation functions

#ifndef FUNC_CONNECT_H
#define FUNC_CONNECT_H

#include <vector>
#include <tuple>
#include <unordered_map>

#include <algorithm>


namespace generation {

/*
 * Typedefs and struct for edge unordered map definition.
 */

typedef std::tuple<size_t, size_t> edge_t;

struct key_hash : public std::unary_function<edge_t, std::size_t>
{
   std::size_t operator()(const edge_t& k) const
   {
      return std::get<0>(k) ^ std::get<1>(k);
   }
};

struct key_equal : public std::binary_function<edge_t, edge_t, bool>
{
   bool operator()(const edge_t& v0, const edge_t& v1) const
   {
      return ( std::get<0>(v0) == std::get<0>(v1) &&
               std::get<1>(v0) == std::get<1>(v1) );
   }
};

typedef std::unordered_map<edge_t, size_t, key_hash, key_equal> map_t;
typedef std::unordered_map<edge_t, double, key_hash, key_equal> map_proba;


/*
 * Sort a vector to move the N unique numbers in the N first entries.
 *
 * \param a - Source array.
 * 
 * .. note::
 *   The array is modified inplace.
 *
 * \return num_unique - Number of unique entries.
 */
size_t _unique_1d(std::vector<int>& a);


/*
 * Sort a 2-D vector to move the N unique pairs in the N first columns.
 *
 * \param a - Source array.
 * 
 * .. note::
 *   The array is modified inplace.
 *
 * \return num_unique - Number of unique entries.
 */
size_t _unique_2d(std::vector< std::vector<int> >& a);


/*
 * Generate the complementary nodes for desired edges.
 *
 * \param seed           - Seed for the random number generator.
 * \param nodes          - Population from whch to draw the complementary end of the edges.
 * \param other_end      - Node at the other end of the edges.
 * \param degree         - Degree of node `other_end` (length of the returned array)
 * \param existing_edges - 2D-array containing the existing edges.
 * \param multigraph     - Whether multiple edges are allowed.
 *
 * \return result        - The desired vecotr of complementary nodes.
 */
std::vector<size_t> _gen_edge_complement(
  long seed, const std::vector<size_t>& nodes, const size_t other_end,
  const size_t degree, const std::vector< std::vector<size_t> >* existing_edges,
  const bool multigraph);


/*
 * Generate random edges from a list of nodes, their target degrees, and a
 * second population of nodes.
 *
 * \param ia_edges       - Linearized (E, 2) array that will contain the edges
 * \param first_nodes    - Population the degree of which is known.
 * \param degrees        - Degree of each node in `first_nodes`.
 * \param second_nodes   - Population from whch to draw the complementary end of the edges.
 * \param existing_edges - 2D-array containing the existing edges.
 * \param multigraph     - Whether multiple edges are allowed.
 * \param idx            - Index determining source/target from first/second nodes
 * \param directed       - Whether the edges are directed or not.
 * \param msd            - Master seed.
 * \param omp            - Number of OpenMP threads.
 */
void _gen_edges(
  size_t* ia_edges, const std::vector<size_t>& first_nodes,
  const std::vector<size_t>& degrees, const std::vector<size_t>& second_nodes,
  const std::vector< std::vector<size_t> >& existing_edges, unsigned int idx,
  bool multigraph, bool directed, long msd, unsigned int omp);



double _proba(int rule, double scale, double distance);

/*
 * Parallel distance-rule generator.
 * 
 * \param ia_edges       - array that will contain the edges
 * \param source_nodes   - array containing the ids of the source nodes
 * \param target_nodes   - array containing the ids of the target nodes
 * \param rule           - rule for prabability computation ("exp" or "lin")
 * \param scale          - typical distance for probability computation
 * \param x              - x coordinate of the neurons' positions
 * \param y              - y coordinate of the neurons' positions
 * \param area           - total area of the spatial environment
 * \param num_neurons    - total number of neurons
 * \param num_edges      - desired number of edges
 * \param existing_edges - array containing the edges that are already present
 *                         in the graph
 * \param multigraph     - whether the graph can have duplicate edges
 * \param msd            - master seed given by numpy in the cython function
 * \param omp            - number of OpenMP threads
 */
void _cdistance_rule(size_t* ia_edges, const std::vector<size_t>& source_nodes,
  const std::vector<size_t>& target_nodes, const std::string& rule,
  double scale, const std::vector<double>& x, const std::vector<double>& y,
  double area, size_t num_neurons, size_t num_edges,
  const std::vector< std::vector<size_t> >& existing_edges, bool multigraph,
  long msd, unsigned int omp);

}

#endif // FUNC_CONNECT_H
