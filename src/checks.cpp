#include <algorithm>
#include "basedefs.h"
#include "check.h"
#include "graph-algo.h"

Status avoid_overlap(Augmentation& aug, Vector<Matrix<bool>>& positive_sets,
                     Vector<Matrix<bool>>& negative_sets,
                     Vector<Augmentation>& out_aug_list) {
  // negative addition cannot have produced a problem among the positive_sets
  if (std::get<AdditionTo>(aug) == AdditionTo::E_MINUS) return Status::OK;

  auto dimensions = positive_sets.size();
  auto& edge = std::get<Pair<int>>(aug);
  int free_dimensions = 0;
  int free_dim = -1;
  for (size_t dim = 0; dim < dimensions; dim++) {
    if (!positive_sets[dim][edge.first][edge.second]) {
      free_dim = dim;
      if (++free_dimensions == 2) return Status::OK;
    }
  }
  if (free_dimensions == 0) {
    return Status::EXIT;
  }
  negative_sets[free_dim][edge.first][edge.second] = true;
  negative_sets[free_dim][edge.second][edge.first] = true;
  out_aug_list.push_back({edge, AdditionTo::E_MINUS, free_dim});
  return Status::OK;
}

/**
 * TODO: Check whether aug.edge really is in E_PLUS (when sigma == E_PLUS)
 */
Status avoid_C4(Vector<bool>& nodes, Augmentation& aug,
                Vector<Matrix<bool>>& positive_sets,
                Vector<Matrix<bool>>& negative_sets,
                Vector<Augmentation>& out_aug_list) {
  auto& edge = std::get<Pair<int>>(aug);
  auto& dim = std::get<Dimension>(aug);
  auto& neg = negative_sets[dim];
  auto& pos = positive_sets[dim];
  auto i = edge.first;
  auto j = edge.second;
  auto size = nodes.size();

  if (std::get<AdditionTo>(aug) == AdditionTo::E_PLUS) {
    // cycle in order i j k l
    for (size_t k = 0; k < size; k++) {
      if (!nodes[k] || k == i || k == j) continue;
      for (size_t l = 0; l < size; l++) {
        if (!nodes[l] || l == i || l == j || l == k) continue;

        // compute how many edges the cycle C4 is missing in positive set,
        // considering (i,j) is an edge of the cycle
        Pair<int> missing_edge = {-1, -1};
        int missing_count = 0;
        if (!pos[j][k]) {
          missing_count++;
          missing_edge = {j, k};
        }
        if (!pos[k][l]) {
          missing_count++;
          missing_edge = {k, l};
        }
        if (!pos[l][i]) {
          missing_count++;
          missing_edge = {l, i};
        }

        // has 2 chords in negative set
        if (neg[i][k] && neg[j][l]) {
          // if the cycle is complete, search space is already empty
          if (missing_count == 0) return Status::EXIT;
          // is almost complete and the remaining edge is not already in
          // negative set
          if (missing_count == 1 &&
              !neg[missing_edge.first][missing_edge.second]) {
            neg[missing_edge.first][missing_edge.second] = true;
            neg[missing_edge.second][missing_edge.first] = true;
            out_aug_list.push_back({missing_edge, AdditionTo::E_MINUS, dim});
          }
        }

        // has 1 chord in negative set, and the other is not already at positive
        // set. Also, the C4 is complete in the positive set
        if (neg[i][k] && !pos[j][l] && missing_count == 0) {
          // if the other chord already is at negative set, the search is space
          // is empty
          if (neg[j][l]) return Status::EXIT;
          pos[j][l] = true;
          pos[l][j] = true;
          out_aug_list.push_back({{j, l}, AdditionTo::E_PLUS, dim});
        }

        // has 1 chord in negative set, and the other is not already at positive
        // set. Also, the C4 is complete in the positive set
        if (neg[j][l] && !pos[i][k] && missing_count == 0) {
          // if the other chord already is at negative set, the search is space
          // is empty
          if (neg[i][k]) return Status::EXIT;
          pos[i][k] = true;
          pos[k][i] = true;
          out_aug_list.push_back({{i, k}, AdditionTo::E_PLUS, dim});
        }
      }
    }

  } else {  // addition to E_MINUS
    // cycle in order i k j l
    for (size_t k = 0; k < size; k++) {
      if (!nodes[k] || k == i || k == j) continue;
      for (size_t l = 0; l < size; l++) {
        if (!nodes[l] || l == i || l == j || l == k) continue;

        // compute how many edges the cycle C4 is missing in positive set,
        // considering (i,j) is a CHORD of the cycle
        Pair<int> missing_edge = {-1, -1};
        int missing_count = 0;
        if (!pos[i][k]) {
          missing_count++;
          missing_edge = {i, k};
        }
        if (!pos[k][j]) {
          missing_count++;
          missing_edge = {k, j};
        }
        if (!pos[j][l]) {
          missing_count++;
          missing_edge = {j, l};
        }
        if (!pos[l][i]) {
          missing_count++;
          missing_edge = {l, i};
        }

        // if the other chord is also already in negative set
        if (neg[k][l]) {
          // the C4 is unbreakable
          if (missing_count == 0) return Status::EXIT;
          // the C4 is almost complete. Must not let it be completed
          if (missing_count == 1) {
            neg[missing_edge.first][missing_edge.second] = true;
            neg[missing_edge.second][missing_edge.first] = true;
            out_aug_list.push_back({missing_edge, AdditionTo::E_MINUS, dim});
          }
        }

        // if the C4 is complete and the other chord is not already in positive
        // set
        if (missing_count == 0 && !pos[k][l]) {
          // the remaining chord is unusable. Search space is empty
          if (neg[k][l]) return Status::EXIT;
          pos[k][l] = true;
          pos[l][k] = true;
          out_aug_list.push_back({{k, l}, AdditionTo::E_PLUS, dim});
        }
      }
    }
  }

  return Status::OK;
}

Status avoid_infeasible_clique(Vector<bool>& nodes, Augmentation& aug,
                               Vector<Matrix<bool>>& positive_sets,
                               Vector<Matrix<bool>>& negative_sets,
                               Vector<int>& node_costs, int allowed_cost) {
  auto& added_to = std::get<AdditionTo>(aug);
  if (added_to == AdditionTo::E_PLUS) return Status::OK;

  auto size = nodes.size();
  auto& aug_edge = std::get<Edge>(aug);
  auto& neg = negative_sets[std::get<Dimension>(aug)];

  Vector<bool> s0_nodes(size, false);
  Vector<int> s0_nodes_list(0);
  s0_nodes_list.reserve(size);
  // for all nodes connected both to edge.first and edge.second in negative set,
  // they compose the possible infeasible click
  for (size_t i = 0; i < size; i++) {
    if (nodes[i] && neg[i][aug_edge.first] && neg[i][aug_edge.second]) {
      s0_nodes[i] = true;
      s0_nodes_list.push_back(i);
    }
  }

  Vector<Edge> out_cycle;
  auto&& orientation = TransitiveOrientation(s0_nodes, neg, out_cycle);

  // the induced subgraph is a comparability graph: easy
  if (out_cycle.size() == 0) {
    auto&& clique = MaximumClique(s0_nodes, orientation, node_costs);
    int cost = node_costs[aug_edge.first] + node_costs[aug_edge.second];
    for (auto&& i : clique) {
      cost += node_costs[i];
    }
    if (cost > allowed_cost) return Status::EXIT;
  }

  // the induced subgraph is not a comparability one. Searching for a clique is
  // thus NP-hard, and we search greedily
  else {
    Vector<int> clique(0);
    clique.reserve(size);  // maximum capacity is known
    // sort with maximum weight node first (greedy)
    std::sort(
        s0_nodes_list.begin(), s0_nodes_list.end(),
        [&node_costs](int a, int b) { return node_costs[a] > node_costs[b]; });
    for (auto&& candidate : s0_nodes_list) {
      // only append the candidate if it is connected to all the others (i.e.
      // can form a clique with them)
      for (auto&& other : clique) {
        if (!neg[candidate][other]) continue;
      }
      clique.push_back(candidate);
    }

    // check if the clique is infeasible
    int cost = node_costs[aug_edge.first] + node_costs[aug_edge.second];
    for (auto&& i : clique) {
      cost += node_costs[i];
    }
    if (cost > allowed_cost) return Status::EXIT;
  }

  return Status::OK;
}