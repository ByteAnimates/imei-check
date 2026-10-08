// The IMEI Check — O(n)
// As shown in the reel
// Generated from the episode; edits here are overwritten. See the README.

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
