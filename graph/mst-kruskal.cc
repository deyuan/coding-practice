// Minimum Spanning Tree, Kruskal Algorithm
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include "graph_util.h"

class UnionFind {
 public:
  UnionFind(int n) : root(n), rank(n) {
    for (int i = 0; i < n; i++) {
      root[i] = i;
    }
  }

  int find(int x) {
    if (root[x] == x) {
      return root[x];
    }
    return root[x] = find(root[x]);
  }

  void unionSet(int x, int y) {
    int rootX = root[x];
    int rootY = root[y];
    if (rootX != rootY) {
      int rankX = rank[rootX];
      int rankY = rank[rootY];
      if (rankX < rankY) {
        root[rootX] = rootY;
      } else if (rankX > rankY) {
        root[rootY] = rootX;
      } else {
        root[rootY] = rootX;
        rank[rootX] += 1;
      }
    }
  }

  bool isConnected(int x, int y) {
    return find(x) == find(y);
  }
 private:
  std::vector<int> root;
  std::vector<int> rank;
};

int kruskal(int n,
    const std::vector<std::vector<int>> &edges,
    std::vector<std::vector<int>> &mst) {
  // sort all edges by cost
  std::vector<std::tuple<int, int, int>> sortedEdges;
  for (auto& edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int c = edge[2];
    sortedEdges.push_back(std::make_tuple(c, u, v));
  }
  sort(sortedEdges.begin(), sortedEdges.end());

  // build MST with union-find
  UnionFind uf(n);
  int totalCost = 0;
  for (auto& edge : sortedEdges) {
    int u = std::get<1>(edge);
    int v = std::get<2>(edge);
    int c = std::get<0>(edge);
    if (!uf.isConnected(u, v)) {
      totalCost += c;
      uf.unionSet(u, v);
      mst.push_back({u, v});
    }
  }
  return totalCost;
}

int main() {
  // read in graph
  int n = 0;
  std::vector<std::vector<int>> edges;
  ReadWeightedEdgeListFromStdIn(n, edges);

  // test kruskal
  std::vector<std::vector<int>> mst;
  int cost = kruskal(n, edges, mst);

  std::cout << "MST cost (Kruskal): " << cost << std::endl;
  for (auto& edge : mst) {
    std::cout << edge[0] << " " << edge[1] << std::endl;
  }
}
