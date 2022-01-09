// Header File for Common Graph Utilities
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#ifndef GRAPH_GRAPH_UTIL_H_
#define GRAPH_GRAPH_UTIL_H_

#include <iostream>
#include <vector>
#include <stack>

static inline void ReadEdgeListFromStdIn(int &n,
    std::vector<std::vector<int>> &edges) {

  int m = 0;
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u = 0, v = 0;
    std::cin >> u >> v;
    edges.push_back({u, v});
  }

  std::cout << "Read in " << n << " nodes and "
            << edges.size() << " edges" << std::endl;
}

static inline void ReadWeightedEdgeListFromStdIn(int &n,
    std::vector<std::vector<int>> &edges) {

  int m = 0;
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u = 0, v = 0, c = 0;
    std::cin >> u >> v >> c;
    edges.push_back({u, v, c});
  }

  std::cout << "Read in " << n << " nodes and "
            << edges.size() << " weighted edges" << std::endl;
}

static inline void UndirectedEdgeListToAdjList(
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &adj) {

  for (auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
    adj[edge[1]].push_back(edge[0]);
  }

  std::cout << "Converted " << edges.size()
            << " undirected edges to adj list" << std::endl;
}

static inline void DirectedEdgeListToAdjList(
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &adj) {

  for (auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
  }

  std::cout << "Converted " << edges.size()
            << " directed edges to adj list" << std::endl;
}

static inline void DirectedEdgeListToReverseAdjList(
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &adjrev) {

  for (auto& edge : edges) {
    adjrev[edge[1]].push_back(edge[0]);
  }

  std::cout << "Converted " << edges.size()
            << " directed edges to reverse adj list" << std::endl;
}

static inline void DirectedEdgeListToAdjAndCostList(
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &adj,
    std::vector<std::vector<int>> &cost) {

  for (auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
    cost[edge[0]].push_back(edge[2]);
  }

  std::cout << "Converted " << edges.size()
            << " weighted directed edges to adj/cost list" << std::endl;
}

static inline void UndirectedEdgeListToAdjAndCostList(
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &adj,
    std::vector<std::vector<int>> &cost) {

  for (auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
    adj[edge[1]].push_back(edge[0]);
    cost[edge[0]].push_back(edge[2]);
    cost[edge[1]].push_back(edge[2]);
  }

  std::cout << "Converted " << edges.size()
            << " weighted undirected edges to adj/cost list" << std::endl;
}

#endif  // GRAPH_GRAPH_UTIL_H_

