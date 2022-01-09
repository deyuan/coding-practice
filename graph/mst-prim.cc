// Minimum Spanning Tree, Prim Algorithm
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <queue>
#include "graph_util.h"

// MST edges from node can be traked in the queue
int prim(int n,
    const std::vector<std::vector<int>> &adj,
    const std::vector<std::vector<int>> &cost,
    std::vector<std::vector<int>> &mst) {
  int totalCost = 0;
  int count = 0;
  std::vector<int> dist(n, INT_MAX);
  std::priority_queue<std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>> pq;
  pq.push(std::make_pair(0, 0));
  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    int c = top.first;
    int v = top.second;
    if (dist[v] != INT_MAX) {
      continue;
    }
    totalCost += c;
    dist[v] = totalCost;
    count++;
    if (count == n) {
      break;
    }
    for (int i = 0; i < adj[v].size(); i++) {
      int u = adj[v][i];
      int w = cost[v][i];
      if (dist[u] == INT_MAX) {
        pq.push(std::make_pair(w, u));
      }
    }
  }
  return totalCost;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadWeightedEdgeListFromStdIn(n, edges);
  std::vector<std::vector<int>> adj(n);
  std::vector<std::vector<int>> cost(n);
  UndirectedEdgeListToAdjAndCostList(edges, adj, cost);

  // test prim
  std::vector<std::vector<int>> mst;
  int totalCost = prim(n, adj, cost, mst);

  std::cout << "MST cost (Prim): " << totalCost << std::endl;
  for (auto& edge : mst) {
    std::cout << edge[0] << " " << edge[1] << std::endl;
  }
}
