// Topological Sort Kahn Algorithm
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

// Track preorder and postorder during iterative DFS
void TopoSortKahn(const std::vector<std::vector<int>> &adj, int n,
    std::vector<int> &result) {

  // compute indegree
  std::vector<int> indegree(n);
  for (int v = 0; v < n; v++) {
    for (int u : adj[v]) {
      indegree[u]++;
    }
  }

  // push nodes with 0 indegree to queue
  std::queue<int> q;
  for (int v = 0; v < n; v++) {
    if (indegree[v] == 0) {
      q.push(v);
    }
  }

  // topological sort, update indegree
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    result.push_back(v);
    for (int u : adj[v]) {
      indegree[u]--;
      if (indegree[u] == 0) {
        q.push(u);
      }
    }
  }

  // check results if needed
  if (result.size() != n) {  // has cycle
    result.clear();
  }
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  DirectedEdgeListToAdjList(edges, adj);

  // test kahn topo sort
  std::vector<int> result;
  TopoSortKahn(adj, n, result);

  std::cout << "Topological Sort:" << std::endl;
  for (int v : result) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
