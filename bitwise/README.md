## Bitwise Tricks

* Case of English letters
  * 'A' 0x41, 'a' 0x61
  * ' ' 0x20, '_' 0x5f
  * C++ APIs: `std::tolower(char)`, `std::toupper(char)` in `<cctype>`

```
char c;
c = c | ' ';  // to lower
c = c & '_';  // to upper
c = c ^ ' ';  // toggle case
```

* Different sign

```
int a, b;
bool diffSign = ((a ^ b) < 0);
```

* Eliminate least significant bit

```
int n;
n = n & (n - 1);
```

