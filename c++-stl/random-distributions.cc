// Copyright (c) 2018 Deyuan Guo. All rights reserved.
// This file is subject to the terms and conditions defined
// in file 'LICENSE' in this source code package.

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cassert>

// Read an integer from stdin
int ReadInt() {
  int val = 0;
  if (!(std::cin >> val)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return val;
}

// Read a double from stdin
double ReadDouble() {
  double val = 0;
  if (!(std::cin >> val)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return val;
}

//////////////////////////////////////////////////////////////////////////////
// Base class for testing random distributions
//////////////////////////////////////////////////////////////////////////////

class TestRandDist {
 public:
  TestRandDist()
    : rng_(std::random_device()()),
      kNumRolls_(10000), kMinVal_(-20), kMaxVal_(20)
  {}
  virtual ~TestRandDist() {}
  void Run(bool interactive) {
    this->GenerateRandomNumbers(interactive);
    ShowHistogram(values_);
  }
 protected:
  virtual void GenerateRandomNumbers(bool interactive) {
    values_.clear();
  }
  std::mt19937 rng_;          // random number engine
  const int kNumRolls_;       // number of random rolls
  const int kMinVal_;         // global lower bound
  const int kMaxVal_;         // global upper bound
  std::vector<int> values_;   // just store real numbers as int
 private:
  void ShowHistogram(const std::vector<int> &vec);
};

void TestRandDist::ShowHistogram(const std::vector<int> &vec) {
  const char kMark = '#';
  const int kNumMark = 100;
  if (!vec.size()) {
    std::cout << "  Histogram: Empty Data" << std::endl;
    return;
  }

  auto min_max = std::minmax_element(vec.begin(), vec.end());
  int min_val = *min_max.first;
  int max_val = *min_max.second;

  std::vector<int> histogram(max_val - min_val + 1, 0);
  for (auto v : vec) {
    ++histogram[v - min_val];
  }

  std::cout << "  Histogram of " << vec.size() << " numbers in range "
      << "[" << min_val << ", " << max_val << "]:" << std::endl;
  for (int i = 0; i <= max_val - min_val; ++i) {
    std::cout << "  " << std::setw(3) << i + min_val << " : "
        << std::setw(4) << histogram[i] << " : "
        << std::string(histogram[i] * kNumMark / vec.size(), kMark)
        << std::endl;
  }
  std::cout << std::string(100, '-') << std::endl;
  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
// Random Distributions
// Note: Common methods for all distributions: min(), max(), reset(), param()
//////////////////////////////////////////////////////////////////////////////

// A preprocessor macro for generating random values for any distribution
#define GEN_RAND_DATA(T) \
  std::cout << "  Range ("#T"): min = " << dist.min() \
      << ", max = " << dist.max() << std::endl; \
  values_.clear(); \
  for (int i = 0; i < kNumRolls_; ++i) { \
    T val = dist(rng_); \
    if (val < kMinVal_ || val > kMaxVal_) { continue; } \
    values_.push_back(std::floor(val)); \
  }

class TestUniformIntDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::uniform_int_distribution" << std::endl;
    std::cout << "  Hint: Uniform int distribution, p(i) = 1 / (b - a + 1), a <= i <= b\n";
    int a = 0, b = 9;
    if (interactive) {
      std::cout << "  Enter lower-bound (int a): ";
      a = ReadInt();
      std::cout << "  Enter upper-bound (int b): ";
      b = ReadInt();
    }
    std::cout << "  Parameters: a = " << a << ", b = " << b << std::endl;
    std::uniform_int_distribution<int> dist(a, b);
    GEN_RAND_DATA(int);
  }
};

class TestUniformRealDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::uniform_real_distribution" << std::endl;
    std::cout << "  Hint: Uniform real distribution, p(x) = 1 / (b - a), a <= x < b\n";
    double a = -0.5, b = 1.5;
    if (interactive) {
      std::cout << "  Enter lower-bound (double a): ";
      a = ReadDouble();
      std::cout << "  Enter upper-bound (double b): ";
      b = ReadDouble();
    }
    std::cout << "  Parameters: a = " << a << ", b = " << b << std::endl;
    std::uniform_real_distribution<double> dist(a, b);
    GEN_RAND_DATA(double);
  }
};

class TestBernoulliDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::bernoulli_distribution" << std::endl;
    std::cout << "  Hint: Toss a coin, p(true) = p, p(false) = 1 - p\n";
    double p = 0.6;
    if (interactive) {
      std::cout << "  Enter probability of success (double p): ";
      p = ReadDouble();
    }
    std::cout << "  Parameters: p = " << p << std::endl;
    std::bernoulli_distribution dist(p);
    GEN_RAND_DATA(bool);
  }
};

class TestBinomialDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::binomial_distribution" << std::endl;
    std::cout << "  Hint: Number of successful trials among t trials\n";
    int t = 10;
    double p = 0.5;
    if (interactive) {
      std::cout << "  Enter number of total trials (int t): ";
      t = ReadInt();
      std::cout << "  Enter probability of success (double p): ";
      p = ReadDouble();
    }
    std::cout << "  Parameters: t = " << t << ", p = " << p << std::endl;
    std::binomial_distribution<int> dist(t, p);
    GEN_RAND_DATA(int);
  }
};

class TestGeometricDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::geometric_distribution" << std::endl;
    std::cout << "  Hint: Number of unsuccessful trials before next success trial\n";
    double p = 0.5;
    if (interactive) {
      std::cout << "  Enter probability of success (double p): ";
      p = ReadDouble();
    }
    std::cout << "  Parameters: p = " << p << std::endl;
    std::geometric_distribution<int> dist(p);
    GEN_RAND_DATA(int);
  }
};

class TestNegBinomialDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::negative_binomial_distribution" << std::endl;
    std::cout << "  Hint: Number of successful trials before k unsuccessful trials\n";
    int k = 3;
    double p = 0.5;
    if (interactive) {
      std::cout << "  Enter number of unsuccessful trials (int k): ";
      k = ReadInt();
      std::cout << "  Enter probability of success (double p): ";
      p = ReadDouble();
    }
    std::cout << "  Parameters: k = " << k << ", p = " << p << std::endl;
    std::negative_binomial_distribution<int> dist(k, p);
    GEN_RAND_DATA(int);
  }
};

class TestPoissonDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::poisson_distribution" << std::endl;
    std::cout << "  Hint: Number of independent events occuring in a fixed interval\n";
    double mean = 4.5;
    if (interactive) {
      std::cout << "  Enter average number of events (double mean): ";
      mean = ReadDouble();
    }
    std::cout << "  Parameters: meam = " << mean << std::endl;
    std::poisson_distribution<int> dist(mean);
    GEN_RAND_DATA(int);
  }
};

class TestExponentialDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::exponential_distribution" << std::endl;
    std::cout << "  Hint: Interval before next random event happens\n";
    double lambda = 0.8;
    if (interactive) {
      std::cout << "  Enter rate of occurence (double lambda): ";
      lambda = ReadDouble();
    }
    std::cout << "  Parameters: lambda = " << lambda << std::endl;
    std::exponential_distribution<double> dist(lambda);
    GEN_RAND_DATA(double);
  }
};

class TestGammaDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::gamma_distribution" << std::endl;
    std::cout << "  Hint: Interval before alpha exponential-distributed events happen\n";
    std::cout << "        Exponential distribution if alpha = 1 and beta = 1 / lambda\n";
    double alpha = 3.0, beta = 0.8;
    if (interactive) {
      std::cout << "  Enter shape parameter (double alpha): ";
      alpha = ReadDouble();
      std::cout << "  Enter scale parameter (double beta): ";
      beta = ReadDouble();
    }
    std::cout << "  Parameters: alpha = " << alpha << ", beta = " << beta
        << std::endl;
    std::gamma_distribution<double> dist(alpha, beta);
    GEN_RAND_DATA(double);
  }
};

class TestWeibullDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::weibull_distribution" << std::endl;
    std::cout << "  Hint: Lifetime for which p(death) is proportional to time^a \n";
    std::cout << "        Exponential distribution if a = 1 and b = 1 / lambda\n";
    double a = 2.0, b = 4.0;
    if (interactive) {
      std::cout << "  Enter shape parameter (double a): ";
      a = ReadDouble();
      std::cout << "  Enter scale parameter (double b): ";
      b = ReadDouble();
    }
    std::cout << "  Parameters: a = " << a << ", b = " << b << std::endl;
    std::weibull_distribution<double> dist(a, b);
    GEN_RAND_DATA(double);
  }
};

class TestExtremeValueDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::extreme_value_distribution" << std::endl;
    std::cout << "  Hint: Extreme value among a number of samples\n";
    double a = 2.0, b = 4.0;
    if (interactive) {
      std::cout << "  Enter location parameter (double a): ";
      a = ReadDouble();
      std::cout << "  Enter scale parameter (double b): ";
      b = ReadDouble();
    }
    std::cout << "  Parameters: a = " << a << ", b = " << b << std::endl;
    std::extreme_value_distribution<double> dist(a, b);
    GEN_RAND_DATA(double);
  }
};

class TestNormalDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::normal_distribution" << std::endl;
    std::cout << "  Hint: Aggregation of independent random variables\n";
    double mean = 5.0, stddev = 2.0;
    if (interactive) {
      std::cout << "  Enter mean (double mean): ";
      mean = ReadDouble();
      std::cout << "  Enter stddev (double stddev): ";
      stddev = ReadDouble();
    }
    std::cout << "  Parameters: mean = " << mean << ", stddev = " << stddev
        << std::endl;
    std::normal_distribution<double> dist(mean, stddev);
    GEN_RAND_DATA(double);
  }
};

class TestLogNormalDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::lognormal_distribution" << std::endl;
    std::cout << "  Hint: Logarithm of random values are normally distributed\n";
    double mean = 0.0, stddev = 1.0;
    if (interactive) {
      std::cout << "  Enter underlying mean (double mean): ";
      mean = ReadDouble();
      std::cout << "  Enter underlying stddev (double stddev): ";
      stddev = ReadDouble();
    }
    std::cout << "  Parameters: mean = " << mean << ", stddev = " << stddev
        << std::endl;
    std::lognormal_distribution<double> dist(mean, stddev);
    GEN_RAND_DATA(double);
  }
};

class TestChiSquaredDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::chi_squared_distribution" << std::endl;
    std::cout << "  Hint: Sum of square of standard normal random variables (mean = 0 and stddev = 1)\n";
    double n = 3.0;
    if (interactive) {
      std::cout << "  Enter degree of freedom (double n): ";
      n = ReadDouble();
    }
    std::cout << "  Parameters: n = " << n << std::endl;
    std::chi_squared_distribution<double> dist(n);
    GEN_RAND_DATA(double);
  }
};

class TestCauchyDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::cauchy_distribution" << std::endl;
    std::cout << "  Hint: Dividing two independent standard normal random variables (mean = 0 and stddev = 1)\n";
    double a = 0.0, b = 2.0;
    if (interactive) {
      std::cout << "  Enter location of the peak (double a): ";
      a = ReadDouble();
      std::cout << "  Enter scale parameter (double b): ";
      b = ReadDouble();
    }
    std::cout << "  Parameters: a = " << a << ", b = " << b << std::endl;
    std::cauchy_distribution<double> dist(a, b);
    GEN_RAND_DATA(double);
  }
};

class TestFisherFDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::fisher_f_distribution" << std::endl;
    std::cout << "  Hint: Dividing two independent chi-squared distributions of m and n degrees of freedom\n";
    double m = 2.0, n = 2.0;
    if (interactive) {
      std::cout << "  Enter numerator's degrees of freedom (double m): ";
      m = ReadDouble();
      std::cout << "  Enter denominator's degrees of freedom (double n): ";
      n = ReadDouble();
    }
    std::cout << "  Parameters: m = " << m << ", n = " << n << std::endl;
    std::fisher_f_distribution<double> dist(m, n);
    GEN_RAND_DATA(double);
  }
};

class TestStudentTDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::student_t_distribution" << std::endl;
    std::cout << "  Hint: Average of n normally distributed random variables with same mean but unknown stddev\n";
    double n = 5.0;
    if (interactive) {
      std::cout << "  Enter degrees of freedom (double n): ";
      n = ReadDouble();
    }
    std::cout << "  Parameters: n = " << n << std::endl;
    std::student_t_distribution<double> dist(n);
    GEN_RAND_DATA(double);
  }
};

class TestDiscreteDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::discrete_distribution" << std::endl;
    std::cout << "  Hint: Discrete distribution with weights\n";
    std::vector<double> weights{1, 2, 1, 2, 1, 2};
    if (interactive) {
      weights.clear();
      std::cout << "  Enter number of discrete values (int n): ";
      int n = ReadInt();
      for (int i = 0; i < n; ++i) {
        std::cout << "  Enter weight[" << i << "] (double w): ";
        double w = ReadDouble();
        weights.push_back(w);
      }
    }
    std::cout << "  Parameters: weights = { ";
    for (auto w : weights) std::cout << w << " ";
    std::cout << "}" << std::endl;
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    GEN_RAND_DATA(int);
  }
};

class TestPiecewiseConstantDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::piecewise_constant_distribution" << std::endl;
    std::cout << "  Hint: Constant weight for each interval\n";
    std::vector<double> intervals {0.0, 2.0, 3.0, 5.0, 10.0};
    std::vector<double> weights {4, 4, 2, 1};
    assert(intervals.size() == weights.size() + 1);
    if (interactive) {
      intervals.clear();
      weights.clear();
      std::cout << "  Enter number of intervals (int n): ";
      int n = ReadInt();
      for (int i = 0; i <= n; ++i) {
        std::cout << "  Enter interval endpoint[" << i << "] (double p): ";
        double p = ReadDouble();
        intervals.push_back(p);
      }
      for (int i = 0; i < n; ++i) {
        std::cout << "  Enter weight[" << i << "] (double i): ";
        double w = ReadDouble();
        weights.push_back(w);
      }
    }
    std::cout << "  Parameters: intervals = { ";
    for (auto p : intervals) std::cout << p << " ";
    std::cout << "}, weights = { ";
    for (auto w : weights) std::cout << w << " ";
    std::cout << "}" << std::endl;
    std::piecewise_constant_distribution<double> dist(
        intervals.begin(), intervals.end(), weights.begin());
    GEN_RAND_DATA(double);
  }
};

class TestPiecewiseLinearDist : public TestRandDist {
  virtual void GenerateRandomNumbers(bool interactive) {
    std::cout << "# Test std::piecewise_linear_distribution" << std::endl;
    std::cout << "  Hint: Linear weight for each interval\n";
    std::vector<double> intervals {0.0, 4.0, 8.0, 12.0};
    std::vector<double> weights {4, 0, 4, 2};
    assert(intervals.size() == weights.size());
    if (interactive) {
      intervals.clear();
      weights.clear();
      std::cout << "  Enter number of intervals (int n): ";
      int n = ReadInt();
      for (int i = 0; i <= n; ++i) {
        std::cout << "  Enter interval endpoint[" << i << "] (double p): ";
        double p = ReadDouble();
        intervals.push_back(p);
      }
      for (int i = 0; i <= n; ++i) {
        std::cout << "  Enter endpoint weight[" << i << "] (double i): ";
        double w = ReadDouble();
        weights.push_back(w);
      }
    }
    std::cout << "  Parameters: intervals = { ";
    for (auto p : intervals) std::cout << p << " ";
    std::cout << "}, endpoint weights = { ";
    for (auto w : weights) std::cout << w << " ";
    std::cout << "}" << std::endl;
    std::piecewise_linear_distribution<double> dist(
        intervals.begin(), intervals.end(), weights.begin());
    GEN_RAND_DATA(double);
  }
};

//////////////////////////////////////////////////////////////////////////////
// Main testing entry
//////////////////////////////////////////////////////////////////////////////

void RandomDistributions() {
  std::string opts = "Options:";
  opts += " [1] uniform_int_distribution";
  opts += " [2] uniform_real_distribution";
  opts += " [3] bernoulli_distribution";
  opts += " [4] binomial_distribution";
  opts += " [5] geometric_distribution";
  opts += " [6] negative_binomial_distribution";
  opts += " [7] poisson_distribution";
  opts += " [8] exponential_distribution";
  opts += " [9] gamma_distribution";
  opts += " [10] weibull_distribution";
  opts += " [11] extreme_value_distribution";
  opts += " [12] normal_distribution";
  opts += " [13] lognormal_distribution";
  opts += " [14] chi_squared_distribution";
  opts += " [15] cauchy_distribution";
  opts += " [16] fisher_f_distribution";
  opts += " [17] student_t_distribution";
  opts += " [18] discrete_distribution";
  opts += " [19] piecewise_constant_distribution";
  opts += " [20] piecewise_linear_distribution";
  opts += " [99] Run all";
  opts += " [-1] Exit";

  std::vector<std::unique_ptr<TestRandDist>> dists;
  dists.emplace_back(new TestUniformIntDist());
  dists.emplace_back(new TestUniformRealDist());
  dists.emplace_back(new TestBernoulliDist());
  dists.emplace_back(new TestBinomialDist());
  dists.emplace_back(new TestGeometricDist());
  dists.emplace_back(new TestNegBinomialDist());
  dists.emplace_back(new TestPoissonDist());
  dists.emplace_back(new TestExponentialDist());
  dists.emplace_back(new TestGammaDist());
  dists.emplace_back(new TestWeibullDist());
  dists.emplace_back(new TestExtremeValueDist());
  dists.emplace_back(new TestNormalDist());
  dists.emplace_back(new TestLogNormalDist());
  dists.emplace_back(new TestChiSquaredDist());
  dists.emplace_back(new TestCauchyDist());
  dists.emplace_back(new TestFisherFDist());
  dists.emplace_back(new TestStudentTDist());
  dists.emplace_back(new TestDiscreteDist());
  dists.emplace_back(new TestPiecewiseConstantDist());
  dists.emplace_back(new TestPiecewiseLinearDist());

  // Main testing loop
  while (1) {
    int option = 0;
    std::cout << std::string(100, '=') << "\n" << opts << std::endl;
    do {
      std::cout << "Please enter an integer option: ";
      option = ReadInt();
    } while ((option < 1 || option > 20) && option != 99 && option != -1);
    std::cout << std::endl;

    if (option >= 1 && option <= 20) {
      // Test one distribution in interactive mode
      dists[option - 1]->Run(true);
    } else if (option == 99) {
      // Test all distributions in non-interactive mode
      for (int i = 0; i < dists.size(); ++i) {
        dists[i]->Run(false);
      }
    } else if (option == -1) {
      // Exit
      break;
    }
  }
}

int main() {
  RandomDistributions();
  return 0;
}


