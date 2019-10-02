#pragma once
#include "basedefs.h"

/**
 * If there is no transitive orientation, returns the edges of the 2-chordless
 * cycle via the `out_cycle` arg.
 *
 * Else, returns the class of each edge in the graph:
 *  - m[i][j] > 0 means an outgoing edge (i -> j)
 *  - m[i][j] == 0 means the edge did not exist in the first place
 *  - m[i][j] < 0 means an incoming edge (i <- j)
 */
Matrix<int> TransitiveOrientation(Vector<bool>& nodes, Matrix<bool>& edges,
                                  Vector<Pair<int>>& out_cycle);

Matrix<int> ComplementTransitiveOrientation(Vector<bool>& nodes,
                                            Matrix<bool>& edges,
                                            Vector<Pair<int>>& out_cycle);

/**
 * The clique is maximized with respect to node weights.
 *
 * Returns the list of nodes belonging to the clique.
 */
Vector<int> MaximumClique(Vector<bool>& nodes,
                          Matrix<int>& transitive_orientation,
                          Vector<int>& node_costs);

/**
 * Returns a 4-length vector containing the 4 undirected edges which compose a
 * C4 subgraph. The result is strictly in the order ((i, j), (j, k), (k, l), (l,
 * i)).
 *
 * If there is no induced C4 on the graph, returns an empty vector.
 */
Vector<Pair<int>> C4Cycle(Vector<bool>& nodes, Matrix<bool>& edges);