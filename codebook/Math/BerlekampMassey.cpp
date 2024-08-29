// need add, sub, mul
vector <int> BerlekampMassey(vector <int> a) {
  // find min |c| such that a_n = sum c_j * a_{n - j - 1}, 0-based
  // O(N^2), if |c| = k, |a| >= 2k sure correct
  auto f = [&](vector<int> v, ll c) {
    for (int &x : v) x = mul(x, c);
    return v;
  };
  vector <int> c, best;
  int pos = 0, n = (int)a.size();
  for (int i = 0; i < n; ++i) {
    int error = a[i];
    for (int j = 0; j < (int)c.size(); ++j)
      error = sub(error, mul(c[j], a[i - 1 - j]));
    if (error == 0) continue;
    int inv = Pow(error, mod - 2);
    if (c.empty()) {
      c.resize(i + 1), pos = i, best.pb(inv);
    } else {
      vector <int> fix = f(best, error);
      fix.insert(fix.begin(), i - pos - 1, 0);
      if (fix.size() >= c.size()) {
        best = f(c, sub(0, inv));
        best.insert(best.begin(), inv);
        pos = i, c.resize(fix.size());
      }
      for (int j = 0; j < (int)fix.size(); ++j)
        c[j] = add(c[j], fix[j]);
    }
  }
  return c;
}