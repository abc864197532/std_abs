vector <ll> Mul(vector <ll> a, vector <ll> b, int bound = N) {
  int m = a.size() + b.size() - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  for (int i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);
  ntt(a, true), a.resize(min(m, bound));
  return a;
}
vector <ll> Inverse(vector <ll> a) {
  // O(NlogN), a[0] != 0
  int n = a.size();
  vector <ll> res(1, mpow(a[0], mod - 2));
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    vector <ll> v1(a.begin(), a.begin() + m * 2), v2 = res;
    v1.resize(m * 4), v2.resize(m * 4);
    ntt(v1), ntt(v2);
    for (int i = 0; i < m * 4; ++i) v1[i] = mul(mul(v1[i], v2[i]), v2[i]);
    ntt(v1, true);
    vector <ll> nres(m * 2);
    for (int i = 0; i < m; ++i) nres[i] = add(res[i], res[i]);
    for (int i = 0; i < m * 2; ++i) nres[i] = sub(nres[i], v1[i]);
    res = nres;
  }
  res.resize(n);
  return res;
}
pair <vector <ll>, vector <ll>> Divide(vector <ll> a, vector <ll> b) {
  // a = bQ + R, O(NlogN), b.back() != 0
  int n = a.size(), m = b.size(), k = n - m + 1;
  if (n < m) {
    a.resize(m - 1);
    return {{0}, a};
  }
  vector <ll> tmp = b;
  reverse(all(a)), reverse(all(b)), b.resize(k);
  vector <ll> Q = Mul(a, Inverse(b));
  Q.resize(k), reverse(all(Q)), reverse(all(a));
  vector <ll> res = Mul(tmp, Q), R(m - 1);
  for (int i = 0; i < m - 1; ++i) R[i] = sub(a[i], res[i]);
  return {Q, R};
}
vector <ll> SqrtImpl(vector <ll> a) {
  if (a.empty()) return {0};
  int z = QuadraticResidue(a[0], mod), n = a.size();
  if (z == -1) return {-1};
  vector <ll> q(1, z);
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    vector <ll> fq(all(q));
    fq.resize(m * 2);
    vector <ll> f2 = Mul(fq, fq, m * 2);
    for (int i = 0; i < m * 2; ++i) {
      f2[i] = sub(f2[i], a[i]);
    }
    f2 = Mul(f2, Inverse(fq), m * 2);
    for (int i = 0; i < m * 2; ++i) {
      fq[i] = sub(fq[i], mul(f2[i], (mod + 1) / 2));
    }
    q = fq;
  }
  q.resize(n);
  return q;
}
vector <ll> Sqrt(vector <ll> a) {
  // O(NlogN), return {-1} if not exists
  int n = a.size(), m = 0;
  while (m < n && a[m] == 0) m++;
  if (m == n) return vector <ll>(n);
  if (m & 1) return {-1};
  vector <ll> s = SqrtImpl(vector <ll>(a.begin() + m, a.end()));
  if (s[0] == -1) return {-1};
  vector <ll> res(n);
  for (int i = 0; i < s.size(); ++i) res[i + m / 2] = s[i];
  return res;
}
vector <ll> Derivative(vector <ll> a) {
  int n = a.size();
  vector <ll> res(n - 1);
  for (int i = 0; i < n - 1; ++i) res[i] = mul(a[i + 1], i + 1);
  return res;
}
vector <ll> Integral(vector <ll> a) {
  int n = a.size();
  vector <ll> res(n + 1);
  for (int i = 0; i < n; ++i) {
    res[i + 1] = mul(a[i], mpow(i + 1, mod - 2));
  }
  return res;
}
vector <ll> Ln(vector <ll> a) {
  // O(NlogN), a[0] = 1
  int n = a.size();
  if (n == 1) return {0};
  vector <ll> d = Derivative(a);
  a.pop_back();
  return Integral(Mul(d, Inverse(a), n - 1));
}
vector <ll> Exp(vector <ll> a) {
  // O(NlogN), a[0] = 0
  int n = a.size();
  vector <ll> q(1, 1);
  a[0] = add(a[0], 1);
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    vector <ll> g(a.begin(), a.begin() + m * 2), h(all(q));
    h.resize(m * 2), h = Ln(h);
    for (int i = 0; i < m * 2; ++i) {
      g[i] = sub(g[i], h[i]);
    }
    q = Mul(g, q, m * 2);
  }
  q.resize(n);
  return q;
}
ll FastLinearRecursion(vector <ll> a, vector <ll> c, ll k) {
  // a_n = sigma c_j * a_{n - j - 1}
  // O(NlogNlogK), |a| = |c|, 0-based
  int n = a.size();
  if (k < n) return a[k];
  vector <ll> base(n + 1, 1);
  for (int i = 0; i < n; ++i) base[i] = sub(0, c[i]);
  vector <ll> poly(n);
  (n == 1 ? poly[0] = c[0] : poly[1] = 1);
  auto calc = [&](vector <ll> p1, vector <ll> p2) {
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