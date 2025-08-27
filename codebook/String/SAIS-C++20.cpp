auto sais(const auto &s) {
  const int n = sz(s), z = ranges::max(s) + 1;
  if (n == 1) return vector{0};
  vector<int> c(z); for (int x : s) c[x]++;
  partial_sum(all(c), c.begin());
  vector<int> sa(n); auto I = views::iota(0, n);
  vector<bool> t(n, true);
  for (int i = n - 2; i >= 0; --i)
    t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
  auto is_lms = views::filter([&t](int x) { 
    return x && t[x] && !t[x - 1];
  });
  auto induce = [&] {
    for (auto x = c; int y : sa)
      if (y--) if (!t[y]) sa[x[s[y] - 1]++] = y;
    for (auto x = c; int y : sa | views::reverse)
      if (y--) if (t[y]) sa[--x[s[y]]] = y;
  };
  vector<int> lms, q(n); lms.reserve(n);
  for (auto x = c; int i : I | is_lms)
    q[i] = sz(lms), lms.pb(sa[--x[s[i]]] = i);
  induce(); vector<int> ns(sz(lms));
  for (int j = -1, nz = 0; int i : sa | is_lms) {
    if (j >= 0) {
      int len = min({n - i, n - j, lms[q[i] + 1] - i});
      ns[q[i]] = nz += lexicographical_compare(
          s.begin() + j, s.begin() + j + len,
          s.begin() + i, s.begin() + i + len);
    }
    j = i;
  }
  fill(all(sa), 0); auto nsa = sais(ns);
  for (auto x = c; int y : nsa | views::reverse)
    y = lms[y], sa[--x[s[y]]] = y;
  return induce(), sa;
} // 0eb2d2
struct Suffix {
  // lcp[i] = LCP(sa[i - 1], sa[i])
  int n; vector<int> sa, lcp, rk;
  Suffix(auto _s) : n(sz(_s)), lcp(n), rk(n) {
    vector<int> s(n + 1); // s[n] = 0;
    for (int i = 0; i < n; ++i) s[i] = _s[i];
    // _s shouldn't contain 0
    sa = sais(s), sa.erase(sa.begin());
    for (int i = 0; i < n; ++i) rk[sa[i]] = i;
    for (int i = 0, h = 0; i < n; ++i) {
      if (!rk[i]) { h = 0; continue; }
      for (int j = sa[rk[i] - 1]; max(i, j) + h < n && s[i + h] == s[j + h];) ++h;
      lcp[rk[i]] = h ? h-- : 0;
    }
  }
//int queryLCP(int i, int j) {
//  auto [l, r] = minmax({rk[i] + 1, rk[j] + 1});
//  return lcp_range_min(l, r);
//}
}; // 4422fa