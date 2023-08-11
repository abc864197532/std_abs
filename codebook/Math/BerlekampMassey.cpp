// need add, sub, mul
vector <ll> BerlekampMassey(vector <ll> a) {
  // find min |c| such that a_n = sum c_j * a_{n - j - 1}, 0-based
  // O(N^2), if |c| = k, |a| >= 2k sure correct
  auto f = [&](vector<ll> v, ll c) {
    for (ll &x : v) x = mul(x, c);
    return v;
  };
  vector <ll> c, best;
  int pos = 0, n = a.size();
  for (int i = 0; i < n; ++i) {
    ll error = a[i];
    for (int j = 0; j < c.size(); ++j)
      error = sub(error, mul(c[j], a[i - 1 - j]));
    if (error == 0) continue;
    ll inv = mpow(error, mod - 2);
    if (c.empty()) {
      c.resize(i + 1), pos = i, best.pb(inv);
    } else {
      vector <ll> fix = f(best, error);
      fix.insert(fix.begin(), i - pos - 1, 0);
      if (fix.size() >= c.size()) {
        best = f(c, sub(0, inv));
        best.insert(best.begin(), inv);
        pos = i, c.resize(fix.size());
      }
      for (int j = 0; j < fix.size(); ++j)
        c[j] = add(c[j], fix[j]);
    }
  }
  return c;
}