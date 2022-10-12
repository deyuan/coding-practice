// A C++ implementation of max binary heap
// Deyuan Guo <guodeyuan@gmail.com>
// Date: Oct 10, 2022

#include <vector>
#include <iostream>

//! @class MaxBinaryHeap
//! @brief Max Binary Heap
template <typename T>
class MaxBinaryHeap
{
  public:
    MaxBinaryHeap() {}
    ~MaxBinaryHeap() {}

    // Build a heap in O(n) time
    MaxBinaryHeap(const std::vector<T> data) {
        _heap = data;
        for (int i = parent(_heap.size() - 1); i >= 0; --i) {
            downHeap(i);
        }
    }

    // Insert a new data to heap
    void insert(T data) {
       _heap.push_back(data);
       upHeap(_heap.size() - 1);
    }

    // Extract the max data
    T extractMax() {
        return _heap.front();
    }

    // Delete the max data
    void deleteMax() {
        _heap[0] = _heap.back();
        _heap.pop_back();
        if (!_heap.empty()) {
            downHeap(0);
        }
    }

    // Check if heap is empty
    bool empty() {
        return _heap.empty();
    }

  private:
    // Get the index of parent
    int parent(int idx) {
        return (idx - 1) / 2;
    }

    // Get the index of left child
    int leftChild(int idx) {
        return idx * 2 + 1;
    }

    // Get the index of right child
    int rightChild(int idx) {
        return idx * 2 + 2;
    }

    // Up-heap operation
    void upHeap(int idx) {
        while (idx != 0 && _heap[parent(idx)] < _heap[idx]) {
            std::swap(_heap[parent(idx)], _heap[idx]);
            idx = parent(idx);
        }
    }

    // Down-heap/max-heapify operation
    void downHeap(int idx) {
        int left = leftChild(idx);
        int right = rightChild(idx);
        int largest = idx;
        if (left < _heap.size() && _heap[largest] < _heap[left]) {
            largest = left;
        }
        if (right < _heap.size() && _heap[largest] < _heap[right]) {
            largest = right;
        }
        if (largest != idx) {
            std::swap(_heap[largest], _heap[idx]);
            downHeap(largest);
        }
    }

    std::vector<T> _heap;
};

int main() {
    std::cout << "Test max binary heap" << std::endl;
    MaxBinaryHeap<int> heap;
    heap.insert(1);
    heap.insert(5);
    heap.insert(2);
    heap.insert(3);
    heap.insert(5);
    heap.insert(7);
    heap.insert(10);
    heap.insert(9);
    heap.insert(8);
    heap.insert(5);
    while (!heap.empty()) {
        std::cout << heap.extractMax() << std::endl;
        heap.deleteMax();
    }

    std::cout << "Test max binary heap (build)" << std::endl;
    std::vector<int> data = {1, 5, 2, 3, 5, 7, 10, 9, 8, 5};
    MaxBinaryHeap<int> heap2(data);
    while (!heap2.empty()) {
        std::cout << heap2.extractMax() << std::endl;
        heap2.deleteMax();
    }

    return 0;
}

