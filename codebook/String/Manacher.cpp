// return value only consider string tmp, not s
// return array length = 2N - 1
auto manacher(auto tmp) {
  vector<int> s(1, -1);
  for (auto c : tmp) s.pb(c), s.pb(-1);
  int l = 0, r = 0, n = sz(s);
  vector<int> Z(n);
  for (int i = 0; i < n; ++i) {
    Z[i] = r > i ? min(Z[2 * l - i], r - i) : 1;
    while (i - Z[i] >= 0 && i + Z[i] < n && 
           s[i + Z[i]] == s[i - Z[i]]) Z[i]++;
    if (Z[i] + i > r) l = i, r = Z[i] + i;
  }
  for (int i = 0; i < n; ++i)
    Z[i] = (Z[i] - (i & 1)) / 2 * 2 + (i & 1);
  return vector<int>(1 + all(Z) - 1);
}