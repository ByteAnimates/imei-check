# The IMEI Check

**O(n)**

The working code from the [@ByteAnimates](https://www.facebook.com/ByteAnimates) reel.

```bash
c++ -std=c++17 -O2 -o main main.cpp
./main
```

No dependencies. Any C++17 compiler.

### `imei.cpp`

```cpp
bool valid(const char* s) {
  int sum = 0, n = strlen(s);
  for (int i = 0; i < n; i++) {
    int d = s[n - 1 - i] - '0';
    if (i % 2 == 1) {
      d *= 2;
      if (d > 9) d -= 9;
    }
    sum += d;
  }
  return sum % 10 == 0;
}
```

### Files

| | |
| --- | --- |
| `imei.cpp` | the reel snippet, generated from the episode |
| `main.cpp` | build and run this — the demo, with real inputs and real output |

---

The snippet above is generated from the video itself — what you read is byte-for-byte
what was typed on screen. A fix to it belongs in the episode, so open an issue and the
next reel carries it. Everything else here is hand-written and welcome as a pull request.
