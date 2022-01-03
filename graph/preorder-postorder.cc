// Track DFS visit preorder and postorder
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// Track preorder and postorder during iterative DFS
void TrackOrder(const std::vector<std::vector<int>> &adj, int n,
    std::vector<int> &preorder, std::vector<int> &postorder) {
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
        preorder.push_back(u);
        for (auto v : adj[u]) {
          if (!visited[v]) {
            st.push(v);
          }
        }
      } else if (visited[u] == 1) {
        visited[u] = 2;
        postorder.push_back(u);
      } else {
        st.pop();
      }
    }
  }
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  DirectedEdgeListToAdjList(edges, adj);

  // test preorder and postorder
  std::vector<int> preorder;
  std::vector<int> postorder;
  TrackOrder(adj, n, preorder, postorder);

  // For directed graph, reverse of postorder is a topological sort
  // May need to detect acyclic separately
  std::reverse(postorder.begin(), postorder.end());
  std::cout << "Topological Sort:" << std::endl;
  for (int v : postorder) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
