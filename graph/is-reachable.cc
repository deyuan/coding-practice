// IsReachable
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// IsReachable: Basic DFS, stop if see the target
bool IsReachable(const std::vector<std::vector<int>> &adj, int n, int start, int target) {
  std::vector<int> visited(n);
  std::stack<int> st;
  st.push(start);
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    if (u == target) return true;
    visited[u] = 1;
    for (auto v : adj[u]) {
      if (!visited[v]) {
        st.push(v);
      }
    }
  }
  return false;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  DirectedEdgeListToAdjList(edges, adj);

  // test is reachable
  std::cout << "Reachable matrix:" << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool reachable = IsReachable(adj, n, i, j);
      std::cout << reachable;
    }
    std::cout << std::endl;
  }
}
