// Copyright (c) 2018 Deyuan Guo. All rights reserved.
// This file is subject to the terms and conditions defined
// in file 'LICENSE' in this source code package.

#include <iostream>

int main() {
  unsigned int neg = 0, pos = 0;
  for (unsigned int i = 1; i != 0; i++) {
    float x = i;
    unsigned int j = x;
    if (i < j) {
      pos = std::max(pos, j - i);
    } else if (i > j && j > 100) {
      neg = std::max(neg, i - j);
    }
  }
  std::cout << "Max error (unsigned int -> float -> unsigned int): " << pos << " : " << neg << std::endl;

  neg = 0, pos = 0;
  for (unsigned int i = 1; i != 0; i++) {
    double x = i;
    unsigned int j = x;
    if (i < j) {
      pos = std::max(pos, j - i);
    } else if (i > j && j > 100) {
      neg = std::max(neg, i - j);
    }
  }
  std::cout << "Max error (unsigned int -> double -> unsigned int): " << pos << " : " << neg << std::endl;

  return 0;
}

