#include "graph-algo.h"
#include <iostream>

/**
 * Private helper
 */
void _TransitiveOrientation(Vector<bool>& nodes, Matrix<bool>& edges,
                            Matrix<int>& classes, int i, int j, int k,
                            Vector<Pair<int>>& out_cycle) {
  auto size = nodes.size();
  for (size_t m = 0; m < size; m++) {
    if (!nodes[m]) continue;
    if (edges[i][m] &&
        (!edges[j][m] || (abs(classes[j][m]) < k) && classes[j][m] != 0)) {
      if (classes[i][m] == 0) {
        classes[i][m] = k;
        classes[m][i] = -k;
        _TransitiveOrientation(nodes, edges, classes, i, m, k, out_cycle);
      } else if (classes[i][m] == -k) {
        classes[i][m] = k;
        out_cycle.push_back({i, m});
        // _TransitiveOrientation(nodes, edges, classes, i, m, k, out_cycle);
      }
    }

    if (out_cycle.size() > 0) {
      // I am the end-tip of the cycle
      if (out_cycle[0] == Pair<int>{j, i}) {
        return;
      }
      out_cycle.push_back({i, j});
      return;
    }
  }

  for (size_t m = 0; m < size; m++) {
    if (!nodes[m]) continue;
    if (edges[j][m] &&
        (!edges[i][m] || (abs(classes[i][m]) < k && classes[i][m] != 0))) {
      if (classes[m][j] == 0) {
        classes[m][j] = k;
        classes[j][m] = -k;
        _TransitiveOrientation(nodes, edges, classes, m, j, k, out_cycle);
      } else if (classes[m][j] == -k) {
        classes[m][j] = k;
        out_cycle.push_back({m, j});
        // _TransitiveOrientation(nodes, edges, classes, m, j, k, out_cycle);
      }
    }

    if (out_cycle.size() > 0) {
      // I am the end-tip of the cycle
      if (out_cycle[0] == Pair<int>{j, i}) {
        return;
      }
      out_cycle.push_back({i, j});
      return;
    }
  }
}

Matrix<int> TransitiveOrientation(Vector<bool>& nodes, Matrix<bool>& edges,
                                  Vector<Pair<int>>& out_cycle) {
  out_cycle = {};
  auto size = nodes.size();
  Matrix<int> classes(size);
  for (size_t i = 0; i < size; i++) {
    classes[i] = Vector<int>(size, 0);
  }
  int clazz = 0;
  for (size_t i = 0; i < size; i++) {
    if (!nodes[i]) continue;
    for (size_t j = 0; j < size; j++) {
      if (!nodes[j]) continue;
      if (!edges[i][j]) continue;
      if (classes[i][j] != 0) continue;
      clazz++;
      classes[i][j] = clazz;
      classes[j][i] = -clazz;
      _TransitiveOrientation(nodes, edges, classes, i, j, clazz, out_cycle);
      if (out_cycle.size() > 0) {
        return classes;
      }
    }
  }

  return classes;
}

/**
 * Private helper
 */
void _ComplementTransitiveOrientation(Vector<bool>& nodes, Matrix<bool>& edges,
                                      Matrix<int>& classes, int i, int j, int k,
                                      Vector<Pair<int>>& out_cycle) {
  auto size = nodes.size();
  for (size_t m = 0; m < size; m++) {
    if (!nodes[m]) continue;
    if (!edges[i][m] &&
        (edges[j][m] || (abs(classes[j][m]) < k) && classes[j][m] != 0)) {
      if (classes[i][m] == 0) {
        classes[i][m] = k;
        classes[m][i] = -k;
        _ComplementTransitiveOrientation(nodes, edges, classes, i, m, k,
                                         out_cycle);
      } else if (classes[i][m] == -k) {
        classes[i][m] = k;
        out_cycle.push_back({i, m});
        // _ComplementTransitiveOrientation(nodes, edges, classes, i, m, k,
        // out_cycle);
      }
    }

    if (out_cycle.size() > 0) {
      // I am the end-tip of the cycle
      if (out_cycle[0] == Pair<int>{j, i}) {
        return;
      }
      out_cycle.push_back({i, j});
      return;
    }
  }

  for (size_t m = 0; m < size; m++) {
    if (!nodes[m]) continue;
    if (!edges[j][m] &&
        (edges[i][m] || (abs(classes[i][m]) < k && classes[i][m] != 0))) {
      if (classes[m][j] == 0) {
        classes[m][j] = k;
        classes[j][m] = -k;
        _ComplementTransitiveOrientation(nodes, edges, classes, m, j, k,
                                         out_cycle);
      } else if (classes[m][j] == -k) {
        classes[m][j] = k;
        out_cycle.push_back({m, j});
        // _ComplementTransitiveOrientation(nodes, edges, classes, m, j, k,
        // out_cycle);
      }
    }

    if (out_cycle.size() > 0) {
      // I am the end-tip of the cycle
      if (out_cycle[0] == Pair<int>{j, i}) {
        return;
      }
      out_cycle.push_back({i, j});
      return;
    }
  }
}

Matrix<int> ComplementTransitiveOrientation(Vector<bool>& nodes,
                                            Matrix<bool>& edges,
                                            Vector<Pair<int>>& out_cycle) {
  out_cycle = {};
  auto size = nodes.size();
  Matrix<int> classes(size);
  for (size_t i = 0; i < size; i++) {
    classes[i] = Vector<int>(size, 0);
  }
  int clazz = 0;
  for (size_t i = 0; i < size; i++) {
    if (!nodes[i]) continue;
    for (size_t j = 0; j < size; j++) {
      if (!nodes[j]) continue;
      if (edges[i][j]) continue;
      if (classes[i][j] != 0) continue;
      clazz++;
      classes[i][j] = clazz;
      classes[j][i] = -clazz;
      _ComplementTransitiveOrientation(nodes, edges, classes, i, j, clazz,
                                       out_cycle);
      if (out_cycle.size() > 0) {
        return classes;
      }
    }
  }

  return classes;
}

enum FOLLOW_STATUS { UNEXPLORED = -2, NO_FOLLOW = -1 };

/**
 * Private helper
 */
void _MaximumClique(Vector<bool>& nodes, Matrix<int>& transitive_orientation,
                    Vector<int>& node_costs, Vector<int>& follow,
                    Vector<int>& cumulative_costs, int v) {
  auto size = nodes.size();
  bool has_adjacency = false;
  int best_cost = -1;
  int best_cost_node = -1;
  for (int i = 0; i < size; i++) {
    if (transitive_orientation[v][i] <= 0) continue;
    has_adjacency = true;
    if (follow[i] == UNEXPLORED) {
      _MaximumClique(nodes, transitive_orientation, node_costs, follow,
                     cumulative_costs, i);
    }
    if (best_cost_node == -1 || cumulative_costs[i] > best_cost) {
      best_cost = cumulative_costs[i];
      best_cost_node = i;
    }
  }

  if (!has_adjacency) {
    cumulative_costs[v] = node_costs[v];
    follow[v] = NO_FOLLOW;
    return;
  }

  cumulative_costs[v] = node_costs[v] + best_cost;
  follow[v] = best_cost_node;
}

Vector<int>
 MaximumClique(Vector<bool>& nodes,
                          Matrix<int>& transitive_orientation,
                          Vector<int>& node_costs) {
  auto size = nodes.size();
  Vector<int> cumulative_costs(node_costs);
  Vector<int> follow(size, UNEXPLORED);
  for (size_t i = 0; i < size; i++) {
    if (!nodes[i]) continue;
    if (follow[i] == UNEXPLORED) {
      _MaximumClique(nodes, transitive_orientation, node_costs, follow,
                     cumulative_costs, i);
    }
  }
  int best_cost = -1;
  int best_cost_node = -1;
  for (size_t i = 0; i < size; i++) {
    if (!nodes[i]) continue;
    if (best_cost_node == -1 || cumulative_costs[i] > best_cost) {
      best_cost = cumulative_costs[i];
      best_cost_node = i;
    }
  }

  Vector<int> clique;
  clique.reserve(size);  // maximum capacity is known
  int next = follow[best_cost_node];
  clique.push_back(best_cost_node);
  while (next != NO_FOLLOW) {
    clique.push_back(next);
    next = follow[next];
  }
  return clique;
}

Vector<Pair<int>> C4Cycle(Vector<bool>& nodes, Matrix<bool>& edges) {
  auto size = nodes.size();
  for (size_t i = 0; i < size; i++) {
    if (!nodes[i]) continue;
    for (size_t j = i + 1; j < size; j++) {
      if (!nodes[j] || !edges[i][j]) continue;
      // edge (i, j)
      for (size_t k = i + 1; k < size; k++) {
        if (!nodes[k] || k == j) continue;
        for (size_t l = k + 1; l < size; l++) {
          if (!nodes[l] || l == j || !edges[k][l]) continue;
          // another edge: (k, l)
          if (edges[j][l] && edges[i][k] && !edges[j][k] && !edges[i][l]) {
            // found a chordless C4
            return {{i, j}, {j, l}, {l, k}, {k, i}};
          } else if (edges[j][k] && edges[i][l] && !edges[j][l] &&
                     !edges[i][k]) {
            // found a chordless C4
            return {{i, j}, {j, k}, {k, l}, {l, i}};
          }
        }
      }
    }
  }
  return {};
}
