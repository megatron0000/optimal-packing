#include "opp.h"
#include <assert.h>
#include "checks.h"
#include "graph-algo.h"

/**
 * Looks correct
 */
Status find_augmentation(Vector<bool>& nodes,
                         Vector<Matrix<bool>>& positive_sets,
                         Vector<Matrix<bool>>& negative_sets,
                         Augmentation& out_augmentation, Vector<int> node_costs,
                         int allowed_cost) {
  auto dims = positive_sets.size();
  enum class Cause { CYCLE, CLIQUE, CHORDS, NONE };
  Vector<Edge> cycle;
  Vector<int> clique;
  Vector<Edge> chords;

  for (size_t dim = 0; dim < dims; dim++) {
    Cause cause = Cause::NONE;
    auto& pos = positive_sets[dim];
    auto& neg = negative_sets[dim];
    auto&& orientation = ComplementTransitiveOrientation(nodes, pos, cycle);

    // if is not a comparability graph
    if (cycle.size() != 0) {
      cause = Cause::CYCLE;
    } else {
      clique = std::move(MaximumClique(nodes, orientation, node_costs));
      int cost = 0;
      for (auto&& i : clique) {
        cost += node_costs[i];
      }
      if (cost > allowed_cost) {
        cause = Cause::CLIQUE;
      } else {
        auto&& cycle_edges = C4Cycle(nodes, pos);
        if (chords.size() != 0) {
          cause = Cause::CHORDS;
          chords = {{cycle_edges[0].first, cycle_edges[2].first},
                    {cycle_edges[1].first, cycle_edges[3].first}};
        }
      }
    }

    if (cause == Cause::NONE) continue;

    // same logic, re-written for all 3 particular container cases
    if (cause == Cause::CYCLE) {
      Edge chosen;
      int count = 0;
      for (auto&& i : cycle) {
        if (neg[i.first][i.second]) continue;
        chosen = i;
        if (++count == 2) break;
      }
      if (count == 0) return Status::EXIT;
      out_augmentation = {chosen, AdditionTo::E_PLUS, dim};
      if (count == 1) return Status::FIX;
      return Status::BRANCH;
    }

    if (cause == Cause::CLIQUE) {
      Edge chosen;
      int count = 0;
      auto size = clique.size();
      bool found_two = false;
      for (size_t i = 0; i < size && !found_two; i++) {
        auto clique_i = clique[i];
        for (size_t j = i + 1; j < size; j++) {
          auto clique_j = clique[j];
          if (neg[clique_i][clique_j]) continue;
          chosen = {clique_i, clique_j};
          if (++count == 2) {
            found_two = true;
            break;
          }
        }
      }
      if (count == 0) return Status::EXIT;
      out_augmentation = {chosen, AdditionTo::E_PLUS, dim};
      if (count == 1) return Status::FIX;
      return Status::BRANCH;
    }

    if (cause == Cause::CHORDS) {
      Edge chosen;
      int count = 0;
      for (auto&& i : chords) {
        if (neg[i.first][i.second]) continue;
        chosen = i;
        if (++count == 2) break;
      }
      if (count == 0) return Status::EXIT;
      out_augmentation = {chosen, AdditionTo::E_PLUS, dim};
      if (count == 1) return Status::FIX;
      return Status::BRANCH;
    }
  }

  return Status::OK;
}

Status incorporate_augmentation(Vector<bool>& nodes,
                                Vector<Matrix<bool>>& positive_sets,
                                Vector<Matrix<bool>>& negative_sets,
                                Augmentation& aug, Vector<int>& node_costs,
                                int allowed_cost) {
  auto& edge = std::get<Edge>(aug);
  auto& set = std::get<AdditionTo>(aug);
  auto& dim = std::get<Dimension>(aug);
  auto size = nodes.size();

  Vector<Augmentation> possibilities;
  // means a null initialization. we should initialize by ourselves
  if (dim == -1) {
    int dim_index = 0;
    for (auto&& pos : positive_sets) {
      for (size_t i = 0; i < size; i++) {
        if (!nodes[i]) continue;
        for (size_t j = i + 1; j < size; j++) {
          if (!nodes[j]) continue;
          if (node_costs[i] + node_costs[j] > allowed_cost) {
            pos[i][j] = pos[j][i] = true;
            possibilities.push_back({{i, j}, AdditionTo::E_PLUS, dim_index});
          }
        }
      }
      dim_index++;
    }

  } else if (set == AdditionTo::E_PLUS) {
    auto& pos = positive_sets[dim];
    pos[edge.first][edge.second] = pos[edge.second][edge.first] = true;
    possibilities.push_back(aug);
  } else {  // addition to negative set
    auto& neg = negative_sets[dim];
    neg[edge.first][edge.second] = neg[edge.second][edge.first] = true;
    possibilities.push_back(aug);
  }

  while (possibilities.size() > 0) {
    auto new_aug = possibilities.back();
    possibilities.pop_back();

    if (avoid_overlap(new_aug, positive_sets, negative_sets, possibilities) !=
        Status::OK)
      return Status::EXIT;
    if (avoid_C4(nodes, new_aug, positive_sets, negative_sets, possibilities) !=
        Status::OK)
      return Status::EXIT;
    if (avoid_infeasible_clique(nodes, new_aug, positive_sets, negative_sets,
                                node_costs, allowed_cost) != Status::OK)
      return Status::EXIT;
  }

  return Status::OK;
}

Vector<Matrix<bool>> solve_opp(Vector<bool>& nodes, Vector<int>& node_costs,
                               int allowed_cost, int dimensions) {
  auto size = nodes.size();
  Vector<SearchNode> search_space;
  Vector<Matrix<bool>> sets(dimensions);
  for (size_t i = 0; i < dimensions; i++) {
    Matrix<bool> set(size, Vector<bool>(size, false));
    sets[i] = set;
  }

  search_space.push_back(
      SearchNode(sets, sets, {{-1, -1}, AdditionTo::NONE, -1}));

  while (search_space.size() > 0) {
    SearchNode node = std::move(search_space.back());
    search_space.pop_back();
    Augmentation next_aug;
    Status result;
    do {
      if (incorporate_augmentation(nodes, node.positive_sets,
                                   node.negative_sets, node.next_aug,
                                   node_costs, allowed_cost) == Status::EXIT)
        result = Status::EXIT;
      else
        result =
            find_augmentation(nodes, node.positive_sets, node.negative_sets,
                              next_aug, node_costs, allowed_cost);
    } while (result == Status::FIX);

    if (result == Status::OK) {
      return node.positive_sets;
    }

    if (result == Status::BRANCH) {
      search_space.push_back(
          SearchNode(node.positive_sets, node.negative_sets,
                     {std::get<Edge>(next_aug), AdditionTo::E_PLUS,
                      std::get<Dimension>(next_aug)}));
      search_space.push_back(
          SearchNode(node.positive_sets, node.negative_sets,
                     {std::get<Edge>(next_aug), AdditionTo::E_MINUS,
                      std::get<Dimension>(next_aug)}));
    }
  }

  return Vector<Matrix<bool>>(0);
}