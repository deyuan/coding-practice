// Binary Search Details
// Copyright (c) 2021 Deyuan Guo. All Rights Reserved

#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Binary Search                                                             //
///////////////////////////////////////////////////////////////////////////////
class BinarySearch {
 public:
  // LMLT: RMLT + LMEQ
  static int lmlt(const std::vector<int> &data, int target) {
    int idx = rmlt(data, target);
    if (idx != -1) {
      idx = lmeq(data, data[idx]);
    }
    return idx;
  }
  // LMLE: RMLE + LMEQ
  static int lmle(const std::vector<int> &data, int target) {
    int idx = rmle(data, target);
    if (idx != -1) {
      idx = lmeq(data, data[idx]);
    }
    return idx;
  }
  // LMEQ: lower_bound + same check
  static int lmeq(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] < target) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l < data.size() && data[l] == target ? l : -1;
  }
  // LMGE: lower_bound (base case)
  static int lmge(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] < target) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l < data.size() ? l : -1;
  }
  // LMGT: upper_bound (base case)
  static int lmgt(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] > target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l < data.size() ? l : -1;
  }
  // RMLT: lower_bound - 1
  static int rmlt(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] < target) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l > 0 ? l - 1 : -1;
  }
  // RMLE: upper_bound - 1
  static int rmle(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] > target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l > 0 ? l - 1 : -1;
  }
  // RMEQ: upper_bound - 1 + same check
  static int rmeq(const std::vector<int> &data, int target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (data[mid] > target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l > 0 && data[l - 1] == target ? l - 1 : -1;
  }
  // RMGE: LMGE + RMEQ
  static int rmge(const std::vector<int> &data, int target) {
    int idx = lmge(data, target);
    if (idx != -1) {
      idx = rmeq(data, data[idx]);
    }
    return idx;
  }
  // RMGE: LMGT + RMEQ
  static int rmgt(const std::vector<int> &data, int target) {
    int idx = lmgt(data, target);
    if (idx != -1) {
      idx = rmeq(data, data[idx]);
    }
    return idx;
  }
};

///////////////////////////////////////////////////////////////////////////////
// Main Function for Testing                                                 //
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  std::cout << "Binary Search" << std::endl;

  std::vector<int> data = {1, 1, 2, 2, 4, 4, 6, 6};

  std::cout << "Vector:";
  for (int n : data) {
    std::cout << " " << n;
  }
  std::cout << std::endl;

  printf("TARGET | LMLT LMLE LMEQ LMGE LMGT RMLT RMLE RMEQ RMGE RMGT\n");
  for (int i = 0; i <= 7; i++) {
    printf("%6d |", i);
    printf(" %4d", BinarySearch::lmlt(data, i));
    printf(" %4d", BinarySearch::lmle(data, i));
    printf(" %4d", BinarySearch::lmeq(data, i));
    printf(" %4d", BinarySearch::lmge(data, i));
    printf(" %4d", BinarySearch::lmgt(data, i));
    printf(" %4d", BinarySearch::rmlt(data, i));
    printf(" %4d", BinarySearch::rmle(data, i));
    printf(" %4d", BinarySearch::rmeq(data, i));
    printf(" %4d", BinarySearch::rmge(data, i));
    printf(" %4d", BinarySearch::rmgt(data, i));
    printf("\n");
  }
}

