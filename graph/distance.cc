// Distance with basic BFS
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

void getDistance(const std::vector<std::vector<int>> &adj, int n,
    int start, std::vector<int> &dist) {

  std::queue<int> q;
  q.push(start);
  dist.resize(n, -1);
  int level = 0;
  while (!q.empty()) {
    int levelSize = q.size();
    for (int i = 0; i < levelSize; i++) {
      int v = q.front();
      q.pop();
      for (auto u : adj[v]) {
        if (dist[u] == -1) {
          q.push(u);
          dist[u] = level + 1;
        }
      }
    }
    level++;
  }
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  UndirectedEdgeListToAdjList(edges, adj);

  // test distance
  std::cout << "Distance matrix:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::vector<int> dist;
    getDistance(adj, n, i, dist);
    for (int j = 0; j < n; j++) {
      std::cout << dist[j] << " ";
    }
    std::cout << std::endl;
  }
}
