vector <int> build_fail(string s) {
  vector <int> f(s.size() + 1, 0);
  int k = 0;
  for (int i = 1; i < (int)s.size(); ++i) {
    while (k && s[k] != s[i]) k = f[k];
    if (s[k] == s[i]) k++;
    f[i + 1] = k;
  }
  return f;
}
int match(string s, string t) {
  vector <int> f = build_fail(t);
  int k = 0, ans = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    while (k && s[i] != t[k]) k = f[k];
    if (s[i] == t[k]) k++;
    if (k == (int)t.size()) ans++, k = f[k];
  }
  return ans;
}