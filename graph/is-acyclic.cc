// IsAcyclic
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// IsAcyclic: DFS + detect back edge
bool IsAcyclic(const std::vector<std::vector<int>> &adj, int n) {
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
      if (visited[u] == 0) {
        visited[u] = 1;
        for (auto v : adj[u]) {
          if (!visited[v]) {
            st.push(v);
          } else if (visited[v] == 1) {
            return false;  // found cycle
          }
        }
      } else if (visited[u] == 1) {
        visited[u] = 2;
      } else {
        st.pop();
      }
    }
  }
  return true;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  DirectedEdgeListToAdjList(edges, adj);

  // test is acyclic
  bool isAcyclic = IsAcyclic(adj, n);
  std::cout << "Is Acyclic: " << isAcyclic << std::endl;
}
