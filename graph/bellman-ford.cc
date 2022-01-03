// Bellman-Ford: Single source negative weight shortest path
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

void BellmanFord(int n,
    const std::vector<std::vector<int>> &adj,
    const std::vector<std::vector<int>> &cost,
    int start,
    std::vector<int> &dist,
    std::vector<int> &prev) {

  prev.clear();
  prev.resize(n);
  dist.clear();
  dist.resize(n, INT_MAX);
  dist[start] = 0;

  for (int i = 0; i < n - 1; i++) {
    bool updated = false;
    for (int v = 0; v < n; v++) {
      if (dist[v] == INT_MAX) {
        continue;
      }
      for (int j = 0; j < adj[v].size(); j++) {
        int u = adj[v][j];
        int c = cost[v][j];
        if (dist[u] > dist[v] + c) {
          dist[u] = dist[v] + c;
          prev[u] = v;
          updated = true;
        }
      }
    }
    if (!updated) {
      break;
    }
  }
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadWeightedEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  std::vector<std::vector<int>> cost(n);
  DirectedEdgeListToAdjAndCostList(edges, adj, cost);

  // test Bellman Ford
  std::vector<int> dist;
  std::vector<int> prev;
  BellmanFord(n, adj, cost, 0, dist, prev);
  std::cout << "Bellman-Ford shortest path from 0" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "0 -> " << i << ": dist = " << dist[i] << std::endl;
  }
}
