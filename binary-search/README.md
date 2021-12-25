# Binary Search

## Template

* Key details
  * Use `[l, r)`, i.e. `l = 0` and `r = length`
  * Use `while (l < r)`, so that `l == r` when the loop ends
  * Use `mid = l + (r - l) / 2`, so that `l <= mid < r` and to avoid integer overflow
  * Use `l = mid + 1` or `r = l`, so that search space decreases strictly
  * Handle repeated elements when `mid == target`
    * lower_bound: move to left, i.e. `r = l`
    * upper_bound: move to right, i.e. `l == mid + 1`
  * Additional check after while loop, where `l == r`
    * lower_bound/upper_bound: check if `l == length`
    * For other binary search variations

* Template for lower bound
```
int lower_bound(std::vector<int> &data, int target)
{
    int l = 0;
    int r = data.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] < target) {
            l = mid + 1;
        } else {
            r = mid; // move r when equal
        }
    }
    return l == data.size() ? -1 : l;
}
```

* Template for upper bound
```
int upper_bound(std::vector<int> &data, int target)
{
    int l = 0;
    int r = data.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] > target) {
            r = mid;
        } else {
            l = mid + 1; // move l when equal
        }
    }
    return l == data.size() ? -1 : l;
}
```

## Variations

| Tag  | Repeated Elements | Search Condition | Notes |
| :--- | :---------------- | :--------------- | :---- |
| LMGE | Leftmost  | >= | Base case: lower_bound |
| LMGT | Leftmost  | >  | Base case: upper_bound |

| Tag  | Repeated Elements | Search Condition | Notes |
| :--- | :---------------- | :--------------- | :---- |
| RMLT | Rightmost | <  | Variation: lower_bound - 1 |
| RMLE | Rightmost | <= | Variation: upper_bound - 1 |
| LMEQ | Leftmost  | == | Variation: lower_bound, check if is target |
| RMEQ | Rightmost | == | Variation: upper_bound - 1, check if is target |

| Tag  | Repeated Elements | Search Condition | Notes |
| :--- | :---------------- | :--------------- | :---- |
| LMLE | Leftmost  | <= | Composition: (rightmost <=) + (leftmost ==) |
| LMLT | Leftmost  | <  | Composition: (rightmost <) + (leftmost ==) |
| RMGE | Rightmost | >= | Composition: (leftmost >=) + (rightmost ==) |
| RMGT | Rightmost | >  | Composition: (leftmost >) + (rightmost ==) |

## Example
```
Binary Search
Vector: 1 1 2 2 4 4 6 6
TARGET | LMLT LMLE LMEQ LMGE LMGT RMLT RMLE RMEQ RMGE RMGT
     0 |   -1   -1   -1    0    0   -1   -1   -1    1    1
     1 |   -1    0    0    0    2   -1    1    1    1    3
     2 |    0    2    2    2    4    1    3    3    3    5
     3 |    2    2   -1    4    4    3    3   -1    5    5
     4 |    2    4    4    4    6    3    5    5    5    7
     5 |    4    4   -1    6    6    5    5   -1    7    7
     6 |    4    6    6    6   -1    5    7    7    7   -1
     7 |    6    6   -1   -1   -1    7    7   -1   -1   -1
```

