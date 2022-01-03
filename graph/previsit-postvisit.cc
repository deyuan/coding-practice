// Track previsit and postvisit clock tick
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <stack>
#include "graph_util.h"

// Track previsit and postvisit during iterative DFS
void TrackVisit(const std::vector<std::vector<int>> &adj, int n,
    std::vector<int> &previsit, std::vector<int> &postvisit) {
  int clock = 0;
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
        previsit[u] = clock++;
        for (auto v : adj[u]) {
          if (!visited[v]) {
            st.push(v);
          }
        }
      } else if (visited[u] == 1) {
        visited[u] = 2;
        postvisit[u] = clock++;
      } else {
        st.pop();
      }
    }
  }
}

bool IsAcyclicAlt(const std::vector<std::vector<int>> &adj, int n,
    const std::vector<int> &previsit, const std::vector<int> &postvisit) {
  for (int u = 0; u < n; u++) {
    for (int v : adj[u]) {
      // cycle condition: if u is visited during v
      if (previsit[v] > previsit[u] && postvisit[v] < postvisit[u]) {
        return false;
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

  // test previsit and postvisit
  std::vector<int> previsit(n);
  std::vector<int> postvisit(n);
  TrackVisit(adj, n, previsit, postvisit);

  // detect acyclic based on previsit and postvisit
  bool isAcyclic = IsAcyclicAlt(adj, n, previsit, postvisit);
  std::cout << "Is Acyclic: " << isAcyclic << std::endl;
}
