// C++ implementation of union-find data structure
// Copyright (c) 2021 Deyuan Guo. All Rights Reserved

//#include <bits/stdc++.h>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Disjoint Set                                                              //
// with union by rank and path compression                                   //
// Extend: Track number/size of sets                                         //
// Complexity: Time O(nlg*n), Inverse Ackerman Function, Space O(n)          //
///////////////////////////////////////////////////////////////////////////////
class UnionFind {
 public:
  UnionFind(int n) : root(n), rank(n) {
    for (int i = 0; i < n; i++) {
      root[i] = i;
      rank[i] = 1;
    }
  }

  int find(int x) {
    if (x == root[x]) {
      return x;
    }
    return root[x] = find(root[x]);
  }

  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (rank[rootX] > rank[rootY]) {
        root[rootY] = rootX;
      } else if (rank[rootX] < rank[rootY]) {
        root[rootX] = rootY;
      } else {
        root[rootY] = rootX;
        rank[rootX] += 1;
      }
    }
  }

  bool connected(int x, int y) {
    return find(x) == find(y);
  }

 private:
  std::vector<int> root;
  std::vector<int> rank;
};

///////////////////////////////////////////////////////////////////////////////
// Main Function for Testing                                                 //
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  std::cout << "Union-Find" << std::endl;
  UnionFind uf(5);
  uf.unionSet(0, 1);
  uf.unionSet(2, 3);
  uf.unionSet(1, 4);
  for (int i = 0; i < 5; i++) {
    std::cout << "Root of " << i << " is " << uf.find(i) << std::endl;
  }
}

