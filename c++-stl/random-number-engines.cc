// Copyright (c) 2018 Deyuan Guo. All rights reserved.
// This file is subject to the terms and conditions defined
// in file 'LICENSE' in this source code package.

#include <iostream>
#include <random>

// Engine: std::random_device
// Algorithm: True-RNG if entropy() is non-zero, pseudo-RNG otherwise
// Note: Non-deterministic. May throw an exception if not available
void TestRandomDevice() {
  std::cout << "# RNG Engine Test: std::random_devide" << std::endl;
  std::random_device rd;
  std::cout << "  Range: [" << rd.min() << ", " << rd.max() << "]" << std::endl;
  std::cout << "  Entropy: " << rd.entropy()
      << (rd.entropy() ? " (True RNG)" : " (Pseudo RNG)") << std::endl;
  unsigned int randVal = rd();
  std::cout << "  Random Value: " << randVal << std::endl;
  std::cout << std::endl;
}

// Template for testing a pseudo random number engine
template <class T>
void TestPrngEngine(const std::string &name, unsigned int seed) {
  std::cout << "# RNG Engine Test: " << name << " (seed " << seed << ")\n";
  T rng(seed);
  std::cout << "  Range: [" << rng.min() << ", " << rng.max() << "]\n";
  std::cout << "  Random Values: ";
  std::cout << rng() << ", ";
  std::cout << rng() << ", ";
  std::cout << rng() << ", ";
  rng.seed(seed);  // reset seed
  std::cout << "RESET-SEED\n";
  std::cout << "  Random Values: " << rng() << ", ";
  rng.discard(1);  // discard 1 value
  std::cout << "DISCARDED, ";
  std::cout << rng() << "\n";
  std::cout << std::endl;
}

void RandomNumberEngines() {
  // Note: RNG engines below generate uniformly-distributed unsigned int values

  // Note: Implementation-defined, true-RNG or pseudo-RNG, non-deterministic
  TestRandomDevice();
  // Note: Implementation-defined, implemented as one PRNG engine below
  TestPrngEngine<std::default_random_engine>("std::default_random_engine", 0);

  ////////////////////////////////////////////////////////////////////////////
  // std::linear_congruential_engine
  // Algorithm: x = (a * x + c) mod m, period = m
  //
  // Engine Adaptors:
  //   std::shuffle_order_engine: table_size k, shuffle k elements

  // minstd_rand: a = 48271 (prime), c = 0, m = 2^31 - 1, return uint_fast32_t
  TestPrngEngine<std::minstd_rand>("std::minstd_rand", 0);
  // minstd_rand0: a = 16807 (prime), c = 0, m = 2^31 - 1, return uint_fast32_t
  TestPrngEngine<std::minstd_rand0>("std::minstd_rand0", 0);
  // knuth_b: minstd_rand0 + shuffle_order_engine with k = 256, uint_fast32_t
  TestPrngEngine<std::knuth_b>("std::knuth_b", 0);

  ////////////////////////////////////////////////////////////////////////////
  // std::mersenne_twister_engine
  // Algorithm: word_size w, state_size n, shift_size m, mask_bits r
  //            range = [0, 2^w - 1], period = 2^((n - 1) * w) - 1

  // mt19937: (w, n, m, r) = (32, 624, 397, 31), return uint_fast32_t
  TestPrngEngine<std::mt19937>("std::mt19937", 0);
  // mt19937: (w, n, m, r) = (64, 312, 156, 31), return uint_fast64_t
  TestPrngEngine<std::mt19937_64>("std::mt19937_64", 0);

  ////////////////////////////////////////////////////////////////////////////
  // std::subtract_with_carry_engine
  // Algorithm: lagged fibonacci generator (LFG/LFib)
  //            word_size w, short_lag s, long_lag r
  //
  // Engine Adaptors:
  //   std::discard_block_engine: block_size p, used_block r
  //                              discard p - r elements

  // ranlux24_base: (w, s, r) = (24, 10, 24), return uint_fast32_t
  TestPrngEngine<std::ranlux24_base>("std::ranlux24_base", 0);
  // ranlux48_base: (w, s, r) = (48, 5, 12), return uint_fast64_t
  TestPrngEngine<std::ranlux48_base>("std::ranlux48_base", 0);
  // ranlux24_base + discard_block_engine (p, r) = (223, 23), uint_fast32_t
  TestPrngEngine<std::ranlux24>("std::ranlux24", 0);
  // ranlux48_base + discard_block_engine (p, r) = (389, 11), uint_fast64_t
  TestPrngEngine<std::ranlux48>("std::ranlux48", 0);

  ////////////////////////////////////////////////////////////////////////////
  // Engine Adaptors:
  //   std::independent_bits_engine: work_size w, fixed w bits of each number
}

int main() {
  RandomNumberEngines();
  return 0;
}


