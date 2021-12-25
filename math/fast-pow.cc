// Fast power
// Copyright (c) 2021 Deyuan Guo. All Rights Reserved

#include <iostream>

double fastPow(double x, int n) {
  // case: x is 0
  if (x == 0.0) {
    return 0.0;
  }
  // case: negative exponent, use long long to avoid integer overflow
  long long N = n;
  if (N < 0) {
    x = 1.0 / x;
    N = -N;
  }
  // compute power per bit
  double result = 1.0;
  double prod = x;
  for (long long i = N; i > 0; i >>= 1) {
    if (i & 1) {
      result *= prod;
    }
    prod *= prod;
  }
  return result;
}

int main() {
  double res = fastPow(1.1, 5000);
  std::cout << "1.1 ^ 5000 = " << res << std::endl;
}

