// return value only consider string tmp, not s
vector <int> manacher(string tmp) {
  string s = "&";
  for (char c : tmp) s.pb(c), s.pb('%');
  int l = 0, r = 0, n = s.size();
  vector <int> Z(n);
  for (int i = 0; i < n; ++i) {
    Z[i] = r > i ? min(Z[2 * l - i], r - i) : 1;
    while (s[i + Z[i]] == s[i - Z[i]]) Z[i]++;
    if (Z[i] + i > r) l = i, r = Z[i] + i;
  }
  for (int i = 0; i < n; ++i) {
    Z[i] = (Z[i] - (i & 1)) / 2 * 2 + (i & 1);
  }
  return Z;
}