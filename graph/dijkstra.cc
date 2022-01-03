// Dijkstra: Single source non-negative weight shortest path
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

void Dijkstra(int n,
    const std::vector<std::vector<int>> &adj,
    const std::vector<std::vector<int>> &cost,
    int start,
    std::vector<int> &dist,
    std::vector<int> &prev) {

  prev.clear();
  prev.resize(n);
  dist.clear();
  dist.resize(n, INT_MAX);

  // min heap
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>> pq;
  pq.push(std::make_pair(0, start));
  dist[start] = 0;

  while (!pq.empty()) {
    auto node = pq.top();
    pq.pop();
    int d = node.first;
    int v = node.second;
    if (d > dist[v]) {
      continue; // ignore outdated dist
    }
    for (int i = 0; i < adj[v].size(); i++) {
      int u = adj[v][i];
      int c = cost[v][i];
      if (dist[u] == INT_MAX || dist[u] > dist[v] + c) {
        dist[u] = dist[v] + c;
        prev[u] = v;  // for rebuild shortest path
        pq.push(std::make_pair(dist[u], u));
      }
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

  // test Dijkstra
  std::vector<int> dist;
  std::vector<int> prev;
  Dijkstra(n, adj, cost, 0, dist, prev);
  std::cout << "Dijkstra shortest path from 0" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "0 -> " << i << ": dist = " << dist[i] << std::endl;
  }
}
