// A C++ implemnetation of red-black tree (integer tree set)
// with interactive testing
// Reference: Introduction to Algorithms 3rd Edition
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>
// Date: Dec 12, 2021

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Red-Black Tree Class
class RBTree {
 public:
  RBTree() {
    nil_ = new Node(INT_MIN);
    root_ = nil_;
    size_ = 0;
    verbose_ = true;
  }
  ~RBTree() {
    delete nil_;
  }

  int Size() { return size_; }
  bool HasKey(int k);
  void Insert(int k);
  void Delete(int k);
  void Print();

 private:
  static const bool kBlack = false;
  static const bool kRed = true;

  struct Node {
    explicit Node(int k)
      : key(k), left(nullptr), right(nullptr), p(nullptr), color(kBlack) {}
    int key;
    Node* left;
    Node* right;
    Node* p;
    bool color;
  };

  Node* Find(int k);
  void PrintHelper(Node* x, int level);

  // Key implementation
  void LeftRotate(Node* x);
  void RightRotate(Node* x);
  void RBInsert(Node* z);
  void RBInsertFixup(Node* z);
  void RBTransplant(Node* u, Node* v);
  Node* TreeMinimum(Node* z);
  void RBDelete(Node* z);
  void RBDeleteFixup(Node* x);

  Node* root_;
  Node* nil_;
  int size_;
  bool verbose_;
};

///////////////////////////////////////////////////////////////////////////////
// Utility APIs
///////////////////////////////////////////////////////////////////////////////

bool RBTree::HasKey(int k) {
  Node* t = Find(k);
  return t != nil_;
}

void RBTree::Insert(int k) {
  Node* t = Find(k);
  if (t == nil_) {
    Node *z = new Node(k);
    RBInsert(z);
    ++size_;
  }
}

void RBTree::Delete(int k) {
  Node* t = Find(k);
  if (t != nil_) {
    RBDelete(t);
    --size_;
  }
}

RBTree::Node* RBTree::Find(int k) {
  Node *t = root_;
  while (t != nil_) {
    if (k < t->key) {
      t = t->left;
    } else if (k > t->key) {
      t = t->right;
    } else {
      return t;
    }
  }
  return nil_;
}

void RBTree::Print() {
  cout << "* RBTree (size = " << size_ << "):" << endl;;
  PrintHelper(root_, 1);
}

void RBTree::PrintHelper(RBTree::Node* x, int level) {
  if (x != nil_) {
    PrintHelper(x->left, level + 1);
    for (int i = 0; i < level; i++) {
      cout << "  ";
    }
    cout << x->key;
    if (x->color == kBlack) {
      cout << " (B)";
    } else {
      cout << " (R)";
    }
    cout << endl;
    PrintHelper(x->right, level + 1);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Key Implementation
///////////////////////////////////////////////////////////////////////////////

void RBTree::LeftRotate(RBTree::Node* x) {
  if (verbose_) {
    cout << "LOG: LeftRotate " << x->key << endl;
  }
  Node* y = x->right;
  x->right = y->left;
  if (y->left != nil_) {
    y->left->p = x;
  }
  y->p = x->p;
  if (x->p == nil_) {
    root_ = y;
  } else if (x == x->p->left) {
    x->p->left = y;
  } else {
    x->p->right = y;
  }
  y->left = x;
  x->p = y;
}

void RBTree::RightRotate(RBTree::Node* x) {
  if (verbose_) {
    cout << "LOG: RightRotate " << x->key << endl;
  }
  Node* y = x->left;
  x->left = y->right;
  if (y->right != nil_) {
    y->right->p = x;
  }
  y->p = x->p;
  if (x->p == nil_) {
    root_ = y;
  } else if (x == x->p->left) {
    x->p->left = y;
  } else {
    x->p->right = y;
  }
  y->right = x;
  x->p = y;
}

void RBTree::RBInsert(RBTree::Node* z) {
  if (verbose_) {
    cout << "LOG: RBInsert " << z->key << endl;
  }
  Node* y = nil_;
  Node* x = root_;
  while (x != nil_) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->p = y;
  if (y == nil_) {
    root_ = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = nil_;
  z->right = nil_;
  z->color = kRed;
  RBInsertFixup(z);
}

void RBTree::RBInsertFixup(RBTree::Node *z) {
  if (verbose_) {
    cout << "LOG: RBInsertFixup " << z->key << endl;
  }
  while (z->p->color == kRed) {
    if (z->p == z->p->p->left) {
      Node* y = z->p->p->right;
      if (y->color == kRed) {
        z->p->color = kBlack;
        y->color = kBlack;
        z->p->p->color = kRed;
        z = z->p->p;
      } else {
        if (z == z->p->right) {
          z = z->p;
          LeftRotate(z);
        }
        z->p->color = kBlack;
        z->p->p->color = kRed;
        RightRotate(z->p->p);
      }
    } else {
      Node* y = z->p->p->left;
      if (y->color == kRed) {
        z->p->color = kBlack;
        y->color = kBlack;
        z->p->p->color = kRed;
        z = z->p->p;
      } else {
        if (z == z->p->left) {
          z = z->p;
          RightRotate(z);
        }
        z->p->color = kBlack;
        z->p->p->color = kRed;
        LeftRotate(z->p->p);
      }
    }
  }
  root_->color = kBlack;
}

void RBTree::RBTransplant(RBTree::Node* u, RBTree::Node* v) {
  if (verbose_) {
    cout << "LOG: RBTransplant " << u->key << " with " << v->key << endl;
  }
  if (u->p == nil_) {
    root_ = v;
  } else if (u == u->p->left) {
    u->p->left = v;
  } else {
    u->p->right = v;
  }
  v->p = u->p;
}

RBTree::Node* RBTree::TreeMinimum(RBTree::Node* z) {
  if (verbose_) {
    cout << "LOG: TreeMinimum " << z->key << endl;
  }
  while (z->left != nil_) {
    z = z->left;
  }
  return z;
}

void RBTree::RBDelete(RBTree::Node* z) {
  if (verbose_) {
    cout << "LOG: RBDelete " << z->key << endl;
  }
  Node* x = nil_;
  Node* y = z;
  bool y_orig_color = y->color;
  if (z->left == nil_) {
    x = z->right;
    RBTransplant(z, z->right);
  } else if (z->right == nil_) {
    x = z->left;
    RBTransplant(z, z->left);
  } else {
    y = TreeMinimum(z->right);
    y_orig_color = y->color;
    x = y->right;
    if (y->p == z) {
      x->p = y;
    } else {
      RBTransplant(y, y->right);
      y->right = z->right;
      y->right->p = y;
    }
    RBTransplant(z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }
  if (y_orig_color == kBlack) {
    RBDeleteFixup(x);
  }
}

void RBTree::RBDeleteFixup(RBTree::Node* x) {
  if (verbose_) {
    cout << "LOG: RBDeleteFixup " << x->key << endl;
  }
  while (x != root_ && x->color == kBlack) {
    if (x == x->p->left) {
      Node* w = x->p->right;
      if (w->color == kRed) {
        w->color = kBlack;
        x->p->color = kRed;
        LeftRotate(x->p);
        w = x->p->right;
      }
      if (w->left->color == kBlack && w->right->color == kBlack) {
        w->color = kRed;
        x = x->p;
      } else {
        if (w->right->color == kBlack) {
          w->left->color = kBlack;
          w->color = kRed;
          RightRotate(w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = kBlack;
        w->right->color = kBlack;
        LeftRotate(x->p);
        x = root_;
      }
    } else {
      Node* w = x->p->left;
      if (w->color == kRed) {
        w->color = kBlack;
        x->p->color = kRed;
        RightRotate(x->p);
        w = x->p->left;
      }
      if (w->left->color == kBlack && w->right->color == kBlack) {
        w->color = kRed;
        x = x->p;
      } else {
        if (w->left->color == kBlack) {
          w->right->color = kBlack;
          w->color = kRed;
          LeftRotate(w);
          w = x->p->left;
        }
        w->color = x->p->color;
        x->p->color = kBlack;
        w->left->color = kBlack;
        RightRotate(x->p);
        x = root_;
      }
    }
  }
  x->color = kBlack;
}

///////////////////////////////////////////////////////////////////////////////
// Interactive Testing
///////////////////////////////////////////////////////////////////////////////

int main() {
  RBTree rbt;
  while (1) {
    std::string option;
    cout << "---------------------------------------------------------\n";
    cout << "Please select: [q] exit, [f] find, [i] insert, [d] delete\n";
    cin >> option;
    if (option == "f") {
      int key = 0;
      cout << "Input a key to find: ";
      cin >> key;
      bool found = rbt.HasKey(key);
      cout << "Find key " << key << " in RBTree: " << found << endl;
      rbt.Print();
    } else if (option == "i") {
      int key = 0;
      cout << "Input a key to insert: ";
      cin >> key;
      rbt.Insert(key);
      rbt.Print();
    } else if (option == "d") {
      int key = 0;
      cout << "Input a key to delete: ";
      cin >> key;
      rbt.Delete(key);
      rbt.Print();
    } else if (option == "q") {
      break;
    }
  }
  return 0;
}

