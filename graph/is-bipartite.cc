// Check if a graph is bipartite
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

// Full BFS, assign two colors
bool IsBipartite(const std::vector<std::vector<int>> &adj, int n) {
  std::vector<int> color(n);
  for (int i = 0; i < n; i++) {
    if (color[i]) {
      continue;
    }
    color[i] = 1;
    std::queue<int> q;
    q.push(i);
    int level = 0;
    while (!q.empty()) {
      int levelSize = q.size();
      for (int j = 0; j < levelSize; j++) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
          if (color[u] == 0) {
            q.push(u);
            color[u] = (level % 2 == 1 ? 1 : 2);
          } else if (color[u] == color[v]) {  // color conflict
            return false;
          }
        }
      }
      level++;
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
  UndirectedEdgeListToAdjList(edges, adj);

  // test is bipartite
  bool isBipartite = IsBipartite(adj, n);
  std::cout << "Is bipartite: " << isBipartite << std::endl;
}
