#include <assert.h>
#include <iostream>
#include "basedefs.h"
#include "graph-algo.h"
#include "opp.h"

typedef std::string String;

String ToString(int t) { return std::to_string(t); }
// String ToString(const long& t) { return std::to_string(t); }
// String ToString(const long long& t) { return std::to_string(t); }
// String ToString(const unsigned& t) { return std::to_string(t); }
// String ToString(const unsigned long& t) { return std::to_string(t); }
// String ToString(const unsigned long long& t) { return std::to_string(t); }
// String ToString(const float& t) { return std::to_string(t); }
// String ToString(const double& t) { return std::to_string(t); }

String ToString(Pair<int> p) {
  return "[" + ToString(p.first) + ", " + ToString(p.second) + "]";
}

template <typename T>
String ToString(Vector<T>& v) {
  String result = "{";
  for (size_t j = 0; j < v.size(); j++) {
    if (j > 0) result = result + ", ";
    result = result + ToString(v[j]);
  }
  result = result + "}";
  return result;
}

template <typename T>
String ToString(Matrix<T>& m) {
  String result = "{\n";
  for (size_t i = 0; i < m.size(); i++) {
    if (i > 0) result = result + ", \n";
    result = result + ToString(m[i]);
  }
  result = result + "\n}";
  return result;
}

/*
class Graph {
 private:
  Vector<int> nodes;
  Matrix<int> edges;

 public:
  Graph(Vector<int> nodes, Matrix<int> edges) : nodes(nodes), edges(edges) {}
  virtual int operator[](int i) {

  }
} */

int main() {
  Vector<bool> nodes{1, 0, 1, 1, 1};  // a, none, b, c , d
  Matrix<bool> edges{{0, 0, 1, 1, 1},
                     {0, 0, 0, 0, 0},
                     {1, 0, 0, 1, 1},
                     {1, 0, 1, 0, 0},
                     {1, 0, 1, 0, 0}};

  Vector<Pair<int>> cycle;
  auto orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() == 0);
  std::cout << ToString(orientation) << std::endl;

  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 0, 0}, {0, 1, 0, 1, 1, 0},
           {0, 1, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
  ;
  std::cout << ToString(orientation) << std::endl;

  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 1, 0, 0, 0}, {1, 0, 1, 1, 1, 0}, {1, 1, 0, 0, 1, 1},
           {0, 1, 0, 0, 1, 0}, {0, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
  std::cout << ToString(orientation) << std::endl;

  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 0},
           {0, 0, 1, 0, 1, 0}, {1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
  std::cout << ToString(orientation) << std::endl;
  std::cout << ToString(cycle) << std::endl;

  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 0},
           {0, 0, 1, 0, 1, 0}, {1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
  std::cout << ToString(orientation) << std::endl;
  std::cout << ToString(cycle) << std::endl;

  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 1},
           {0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 1}, {0, 0, 1, 0, 1, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
  std::cout << ToString(orientation) << std::endl;
  std::cout << ToString(cycle) << std::endl;

  nodes = {1, 1, 1, 1};
  edges = {{0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() == 0);
  std::cout << ToString(orientation) << std::endl;
  std::cout << ToString(cycle) << std::endl;

  std::cout << "\n\tMaximum Cliques\n" << std::endl;

  nodes = Vector<bool>(10, true);
  edges = Matrix<bool>(10);
  for (size_t i = 0; i < 10; i++) {
    edges[i] = Vector<bool>(10, false);
  }
  edges[0][1] = true;
  edges[0][3] = true;
  edges[1][0] = true;
  edges[1][2] = true;
  edges[1][3] = true;
  edges[2][1] = true;
  edges[2][3] = true;
  edges[2][4] = true;
  edges[3][0] = true;
  edges[3][1] = true;
  edges[3][2] = true;
  edges[4][2] = true;
  edges[4][5] = true;
  edges[4][9] = true;
  edges[5][4] = true;
  edges[5][6] = true;
  edges[5][9] = true;
  edges[5][8] = true;
  edges[6][5] = true;
  edges[6][7] = true;
  edges[7][6] = true;
  edges[7][8] = true;
  edges[8][7] = true;
  edges[8][9] = true;
  edges[8][5] = true;
  edges[9][8] = true;
  edges[9][4] = true;
  edges[9][5] = true;
  Vector<int> node_costs(10, 1);
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() == 0);
  auto clique = MaximumClique(nodes, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[9] = 2;
  clique = MaximumClique(nodes, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[8] = 2;
  clique = MaximumClique(nodes, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[2] = 10;
  clique = MaximumClique(nodes, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;

  std::cout << "\n\tC4 detection\n" << std::endl;

  nodes = Vector<bool>(10, true);
  edges = Matrix<bool>(10);
  for (size_t i = 0; i < 10; i++) {
    edges[i] = Vector<bool>(10, false);
  }
  edges[0][1] = true;
  edges[0][3] = true;
  edges[1][0] = true;
  edges[1][2] = true;
  edges[1][3] = true;
  edges[2][1] = true;
  edges[2][3] = true;
  edges[2][4] = true;
  edges[3][0] = true;
  edges[3][1] = true;
  edges[3][2] = true;
  edges[4][2] = true;
  edges[4][5] = true;
  edges[4][9] = true;
  edges[5][4] = true;
  edges[5][6] = true;
  edges[5][9] = true;
  edges[5][8] = true;
  edges[6][5] = true;
  edges[6][7] = true;
  edges[7][6] = true;
  edges[7][8] = true;
  edges[8][7] = true;
  edges[8][9] = true;
  edges[8][5] = true;
  edges[9][8] = true;
  edges[9][4] = true;
  edges[9][5] = true;
  cycle = C4Cycle(nodes, edges);
  assert(cycle.size() == 4);
  std::cout << ToString(cycle) << std::endl;
  edges[5][8] = false;
  cycle = C4Cycle(nodes, edges);
  assert(cycle.size() == 0);
  edges[1][3] = false;
  cycle = C4Cycle(nodes, edges);
  assert(cycle.size() == 4);
  std::cout << ToString(cycle) << std::endl;

  nodes = Vector<bool>(78, false);
  Vector<int> costs(78, 0);
  for (size_t i = 0; i < 78; i++) {
    costs[i] = 78 - i;
  }
  int allowed_cost = 100;
  nodes[0] = true;
  nodes[56] = true;
  nodes[57] = true;

  std::cout << "\n\tOPP\n" << std::endl;

  for (auto&& pos : solve_opp(nodes, costs, allowed_cost, 2)) {
    Vector<Edge> list;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = i + 1; j < nodes.size(); j++) {
        if (pos[i][j]) {
          list.push_back({i, j});
        }
      }
    }
    std::cout << ToString(list) << std::endl;
  }
}