auto build_fail(auto s) {
  vector <int> f(sz(s) + 1, 0);
  int k = 0;
  for (int i = 1; i < sz(s); ++i) {
    while (k && s[k] != s[i]) k = f[k];
    if (s[k] == s[i]) k++;
    f[i + 1] = k;
  }
  return f;
}
int match(auto s, auto t) {
  vector <int> f = build_fail(t);
  int k = 0, ans = 0;
  for (int i = 0; i < sz(s); ++i) {
    while (k && s[i] != t[k]) k = f[k];
    if (s[i] == t[k]) k++;
    if (k == sz(t)) ans++, k = f[k];
  }
  return ans;
}