# Transitive orientation

## IN
```cpp
  nodes = {1, 1, 1, 1, 1, 1};
  edges = {{0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 0, 0}, {0, 1, 0, 1, 1, 0},
            {0, 1, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0}};
  orientation = TransitiveOrientation(nodes, edges, cycle);
  assert(cycle.size() != 0);
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
```

## OUT
```ts
  {
  {0, 0, 1, 2, 2}, 
  {0, 0, 0, 0, 0}, 
  {-1, 0, 0, 2, 2}, 
  {-2, 0, -2, 0, 0}, 
  {-2, 0, -2, 0, 0}
  }
  {
  {0, 1, 0, 0, 0, 0}, 
  {1, 0, -1, 1, 0, 0}, 
  {0, 1, 0, 1, 1, 0}, 
  {0, -1, -1, 0, 0, -1}, 
  {0, 0, -1, 0, 0, 0}, 
  {0, 0, 0, 1, 0, 0}
  }
  {
  {0, 1, -1, 0, 0, 0}, 
  {1, 0, -1, -1, 1, 0}, 
  {1, 1, 0, 0, 1, 1}, 
  {0, 1, 0, 0, 1, 0}, 
  {0, -1, -1, -1, 0, -1}, 
  {0, 0, -1, 0, 1, 0}
  }
  {
  {0, 1, 0, 0, 1, 0}, 
  {1, 0, 1, 0, 0, 0}, 
  {0, -1, 0, -1, 0, 0}, 
  {0, 0, 1, 0, 1, 0}, 
  {-1, 0, 0, -1, 0, 0}, 
  {0, 0, 0, 0, 0, 0}
  }
  {[1, 0], [1, 2], [3, 2], [3, 4], [0, 4]}
  {
  {0, 1, 0, 0, 1, 0}, 
  {1, 0, 1, 0, 0, 0}, 
  {0, -1, 0, -1, 0, 0}, 
  {0, 0, 1, 0, 1, 0}, 
  {-1, 0, 0, -1, 0, 0}, 
  {0, 0, 0, 0, 0, 0}
  }
  {[1, 0], [1, 2], [3, 2], [3, 4], [0, 4]}
  {
  {0, 1, 0, 0, 1, 0}, 
  {1, 0, 1, 0, 0, 0}, 
  {0, -1, 0, 0, 0, -1}, 
  {0, 0, 0, 0, 1, 0}, 
  {-1, 0, 0, -1, 0, -1}, 
  {0, 0, 1, 0, 1, 0}
  }
  {[1, 0], [1, 2], [5, 2], [5, 4], [3, 4], [0, 4]}
  {
  {0, 1, 2, 3}, 
  {-1, 0, 2, 3}, 
  {-2, -2, 0, 3}, 
  {-3, -3, -3, 0}
  }
  {}
```

# Maximum clique

## IN
```cpp
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
  auto clique = MaximumClique(nodes, edges, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[9] = 2;
  clique = MaximumClique(nodes, edges, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[8] = 2;
  clique = MaximumClique(nodes, edges, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
  node_costs[2] = 10;
  clique = MaximumClique(nodes, edges, orientation, node_costs);
  std::cout << ToString(clique) << std::endl;
```

## OUT
```ts
        Maximum Cliques

  {0, 1, 3}
  {5, 9, 4}
  {5, 9, 8}
  {2, 1, 3}
```

# C4 detection

## IN
```cpp
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
```


## OUT
```ts
        C4 detection

{[5, 6], [6, 7], [7, 8], [8, 5]}
{[0, 1], [1, 2], [2, 3], [3, 0]}

```

# checks.h

**Untested !!**

