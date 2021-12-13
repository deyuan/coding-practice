# Red-Black Tree

## Notes

* https://en.wikipedia.org/wiki/Red–black_tree
* https://en.wikipedia.org/wiki/2–3–4_tree
* https://en.wikipedia.org/wiki/Left-leaning_red–black_tree

## Testing

```
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 10
LOG: RBInsert 10
LOG: RBInsertFixup 10
* RBTree (size = 1):
  10 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 20
LOG: RBInsert 20
LOG: RBInsertFixup 20
* RBTree (size = 2):
  10 (B)
    20 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 30
LOG: RBInsert 30
LOG: RBInsertFixup 30
LOG: LeftRotate 10
* RBTree (size = 3):
    10 (R)
  20 (B)
    30 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 40
LOG: RBInsert 40
LOG: RBInsertFixup 40
* RBTree (size = 4):
    10 (B)
  20 (B)
    30 (B)
      40 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 50
LOG: RBInsert 50
LOG: RBInsertFixup 50
LOG: LeftRotate 30
* RBTree (size = 5):
    10 (B)
  20 (B)
      30 (R)
    40 (B)
      50 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 60
LOG: RBInsert 60
LOG: RBInsertFixup 60
* RBTree (size = 6):
    10 (B)
  20 (B)
      30 (B)
    40 (R)
      50 (B)
        60 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 70
LOG: RBInsert 70
LOG: RBInsertFixup 70
LOG: LeftRotate 50
* RBTree (size = 7):
    10 (B)
  20 (B)
      30 (B)
    40 (R)
        50 (R)
      60 (B)
        70 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 80
LOG: RBInsert 80
LOG: RBInsertFixup 80
LOG: LeftRotate 20
* RBTree (size = 8):
      10 (B)
    20 (R)
      30 (B)
  40 (B)
      50 (B)
    60 (R)
      70 (B)
        80 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
i
Input a key to insert: 90
LOG: RBInsert 90
LOG: RBInsertFixup 90
LOG: LeftRotate 70
* RBTree (size = 9):
      10 (B)
    20 (R)
      30 (B)
  40 (B)
      50 (B)
    60 (R)
        70 (R)
      80 (B)
        90 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 40
LOG: RBDelete 40
LOG: TreeMinimum 60
LOG: RBTransplant 50 with -2147483648
LOG: RBTransplant 40 with 50
LOG: RBDeleteFixup -2147483648
LOG: LeftRotate 60
* RBTree (size = 8):
      10 (B)
    20 (R)
      30 (B)
  50 (B)
      60 (B)
        70 (R)
    80 (R)
      90 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 50
LOG: RBDelete 50
LOG: TreeMinimum 80
LOG: RBTransplant 60 with 70
LOG: RBTransplant 50 with 60
LOG: RBDeleteFixup 70
* RBTree (size = 7):
      10 (B)
    20 (R)
      30 (B)
  60 (B)
      70 (B)
    80 (R)
      90 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 80
LOG: RBDelete 80
LOG: TreeMinimum 90
LOG: RBTransplant 80 with 90
LOG: RBDeleteFixup -2147483648
* RBTree (size = 6):
      10 (B)
    20 (R)
      30 (B)
  60 (B)
      70 (R)
    90 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: LOG: 30
RBDelete 30
LOG: RBTransplant 30 with -2147483648
LOG: RBDeleteFixup -2147483648
* RBTree (size = 5):
      10 (R)
    20 (B)
  60 (B)
      70 (R)
    90 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 20
LOG: RBDelete 20
LOG: RBTransplant 20 with 10
LOG: RBDeleteFixup 10
* RBTree (size = 4):
    10 (B)
  60 (B)
      70 (R)
    90 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 90
LOG: RBDelete 90
LOG: RBTransplant 90 with 70
LOG: RBDeleteFixup 70
* RBTree (size = 3):
    10 (B)
  60 (B)
    70 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 10
LOG: RBDelete 10
LOG: RBTransplant 10 with -2147483648
LOG: RBDeleteFixup -2147483648
* RBTree (size = 2):
  60 (B)
    70 (R)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 60
LOG: RBDelete 60
LOG: RBTransplant 60 with 70
LOG: RBDeleteFixup 70
* RBTree (size = 1):
  70 (B)
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
d
Input a key to delete: 70
LOG: RBDelete 70
LOG: RBTransplant 70 with -2147483648
LOG: RBDeleteFixup -2147483648
* RBTree (size = 0):
---------------------------------------------------------
Please select: [q] exit, [f] find, [i] insert, [d] delete
q
```
