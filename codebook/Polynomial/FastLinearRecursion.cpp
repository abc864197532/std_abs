ll FastLinearRecursion(vector <ll> a, vector <ll> c, ll k) {
  // a_n = sigma c_j * a_{n - j - 1}, 0-based
  // O(NlogNlogK), |a| = |c|
  int n = a.size();
  if (k < n) return a[k];
  vector <ll> base(n + 1, 1);
  for (int i = 0; i < n; ++i) base[i] = sub(0, c[n - i - 1]);
  vector <ll> poly(n);
  (n == 1 ? poly[0] = c[n - 1] : poly[1] = 1);
  auto calc = [&](vector <ll> p1, vector <ll> p2) {
    // O(n^2) bruteforce or O(nlogn) NTT
    return Divide(Mul(p1, p2), base).second;
  };
  vector <ll> res(n, 0); res[0] = 1;
  for (; k; k >>= 1, poly = calc(poly, poly)) {
    if (k & 1) res = calc(res, poly);
  }
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    (ans += res[i] * a[i]) %= mod;
  }
  return ans;
}