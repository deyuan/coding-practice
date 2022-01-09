# Graph Algorithms

* `graph_util.h` - Common utilities
  * Read edge list from stdin
  * Convert edge list to adjacency list
* `is-reachable.cc` - Check if a node can reach another node
  * Basic DFS from one node
  * Return early if the target node is found
* `connected-components.cc` - Count connected components
  * Full DFS for all unvisited nodes in an undirected graph
  * Count times of DFS
* `is-acyclic.cc` - Check if a graph is acyclic
  * Full DFS + detect back edge to in-visit nodes
    * Track visit status: 0 unseen, 1 in-visit, 2 done
* `previsit-postvisit.cc` - Track previsit/postvisit clock during DFS
  * Alternative way of detecting cycles
    * For an edge (u, v), if u is visited during v: `previsit[u] > previsit[v] && postvisit[u] < postvisit[v]`
* `preorder-postorder.cc` - Track preorder/postorder during DFS
  * Alternative way of topological sort
    * The reversed postorder of an directed acyclic graph is a topological sort
* `topo-sort-kahn.cc` - Topological sort Kahn algorithm
  * Track zero in-degree nodes in a queue
    * Add queue front to result and decrease in-degree of adjacent nodes
* `strongly-cc.cc` - Count strongly connected components
  * 1st DFS on reverse graph to get postorder
  * 2nd DFS on original graph in reversed postorder from 1st DFS and count SCC
* `distance.cc` - Basic BFS
  * BFS to get distance of all nodes from a start node
* `dijkstra.cc` - Dijkstra shortest path algorithm
  * Single-source shortest path on directed graph, non-negative weights only
  * Min heap
* `bellman-ford.cc` - Bellman-Ford shortest path algorithm
  * Single-source shortest path on directed graph, any weights
* `has-neg-cycle.cc` - Detect negative weighted cycle based on Bellman-Ford algorithm
  * Run one more iteration and see if any shortest distance is updated
* `mst-kruskal.cc` - Minimum Spanning Tree, Kruskal algorithm
  * Greedily pick edges
  * Sort edges by weight + union find
* `mst-prim.cc` - Minimum Spanning Tree, Prim algorithm
  * Greedily pick vertices
  * Min heap to get next vertex with minimum weight

