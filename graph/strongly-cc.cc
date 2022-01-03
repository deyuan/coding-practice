// Strongly Connected Components in Directed Graph
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// Strongly Connected Components
int NumStronglyConnectedComponents(const std::vector<std::vector<int>> &edges, int n) {
  // 1st DFS on reverse graph, get postorder
  std::vector<std::vector<int>> adj_rev(n);
  DirectedEdgeListToReverseAdjList(edges, adj_rev);
  std::vector<int> postorder_rev;
  std::vector<int> visited_rev(n);
  for (int v = 0; v < n; v++) {
    if (visited_rev[v]) {
      continue;
    }
    std::stack<int> st;
    st.push(v);
    while (!st.empty()) {
      int u = st.top();
      if (visited_rev[u] == 0) {
        visited_rev[u] = 1;
        for (int w : adj_rev[u]) {
          if (!visited_rev[w]) {
            st.push(w);
          }
        }
      } else if (visited_rev[u] == 1) {
        visited_rev[u] = 2;
        postorder_rev.push_back(u);
      } else {
        st.pop();
      }
    }
  }

  // 2nd DFS on original graph, in reversed postorder from reverse graph
  std::vector<std::vector<int>> adj(n);
  DirectedEdgeListToAdjList(edges, adj);
  std::vector<int> visited(n);
  int scc = 0;
  for (int i = n - 1; i >= 0; i--) {
    int v = postorder_rev[i];
    if (visited[v]) {
      continue;
    }
    std::stack<int> st;
    st.push(v);
    while (!st.empty()) {
      int u = st.top();
      st.pop();
      visited[u] = 1;
      for (int w : adj[u]) {
        if (!visited[w]) {
          st.push(w);
        }
      }
    }
    scc++;
  }

  return scc;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);

  // test strongly connected components
  int scc = NumStronglyConnectedComponents(edges, n);
  std::cout << "# Strongly Connected Components: " << scc << std::endl;
}
