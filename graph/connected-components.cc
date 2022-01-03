// Connected Components in Undirected Graph
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// Connected Components: Full DFS + count
int NumConnectedComponents(const std::vector<std::vector<int>> &adj, int n) {
  int cc = 0;
  std::vector<int> visited(n);
  // full DFS
  for (int i = 0; i < n; i++) {
    if (visited[i]) {
      continue;
    }
    std::stack<int> st;
    st.push(i);
    while (!st.empty()) {
      int u = st.top();
      st.pop();
      visited[u] = 1;
      for (auto v : adj[u]) {
        if (!visited[v]) {
          st.push(v);
        }
      }
    }
    cc++;
  }
  return cc;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  UndirectedEdgeListToAdjList(edges, adj);

  // test connected components
  int cc = NumConnectedComponents(adj, n);
  std::cout << "# Connected Components: " << cc << std::endl;
}
