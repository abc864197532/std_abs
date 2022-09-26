vector <int> manacher(string &s) {
  string t = "^#";
  for (char c : s) t += c, t += '#';
  t += '&';
  int n = t.length();
  vector <int> r(n, 0);
  int C = 0, R = 0;
  for (int i = 1; i < n - 1; ++i) {
    int mirror = 2 * C - i;
    r[i] = (i < R ? min(r[mirror], R - i) : 0);
    while (t[i - 1 - r[i]] == t[i + 1 + r[i]]) r[i]++;
    if (i + r[i] > R) R = i + r[i], C = i;
  }
  return r;
}