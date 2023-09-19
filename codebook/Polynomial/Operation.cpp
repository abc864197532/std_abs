vector <ll> Mul(vector <ll> a, vector <ll> b, int bound = N) {
  int m = a.size() + b.size() - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  vector <ll> out(n);
  for (int i = 0; i < n; ++i) out[i] = mul(a[i], b[i]);
  ntt(out, true), out.resize(min(m, bound));
  return out;
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
    for (int i = 0; i < m * 4; ++i)
      v1[i] = mul(mul(v1[i], v2[i]), v2[i]);
    ntt(v1, true);
    res.resize(m * 2);
    for (int i = 0; i < m; ++i)
      res[i] = add(res[i], res[i]);
    for (int i = 0; i < m * 2; ++i)
      res[i] = sub(res[i], v1[i]);
  }
  res.resize(n);
  return res;
}
pair <vector <ll>, vector <ll>> Divide(vector <ll> a, vector <ll> b) {
  // a = bQ + R, O(NlogN), b.back() != 0
  int n = a.size(), m = b.size(), k = n - m + 1;
  if (n < m) return {{0}, a};
  vector <ll> ra = a, rb = b;
  reverse(all(ra)), ra.resize(k);
  reverse(all(rb)), rb.resize(k);
  vector <ll> Q = Mul(ra, Inverse(rb), k);
  reverse(all(Q));
  vector <ll> res = Mul(b, Q), R(m - 1);
  for (int i = 0; i < m - 1; ++i)
    R[i] = sub(a[i], res[i]);
  return {Q, R};
}
vector <ll> SqrtImpl(vector <ll> a) {
  if (a.empty()) return {0};
  int z = QuadraticResidue(a[0], mod), n = a.size();
  if (z == -1) return {-1};
  vector <ll> q(1, z);
  const int inv2 = (mod + 1) / 2;
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    q.resize(m * 2);
    vector <ll> f2 = Mul(q, q, m * 2);
    for (int i = 0; i < m * 2; ++i)
      f2[i] = sub(f2[i], a[i]);
    f2 = Mul(f2, Inverse(q), m * 2);
    for (int i = 0; i < m * 2; ++i)
      q[i] = sub(q[i], mul(f2[i], inv2));
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
  for (int i = 0; i < s.size(); ++i)
    res[i + m / 2] = s[i];
  return res;
}
vector <ll> Derivative(vector <ll> a) {
  int n = a.size();
  vector <ll> res(n - 1);
  for (int i = 0; i < n - 1; ++i)
    res[i] = mul(a[i + 1], i + 1);
  return res;
}
vector <ll> Integral(vector <ll> a) {
  int n = a.size();
  vector <ll> res(n + 1);
  for (int i = 0; i < n; ++i)
    res[i + 1] = mul(a[i], mpow(i + 1, mod - 2));
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
    for (int i = 0; i < m * 2; ++i)
      g[i] = sub(g[i], h[i]);
    q = Mul(g, q, m * 2);
  }
  q.resize(n);
  return q;
}
vector <ll> Pow(vector <ll> a, ll k) {
  int n = a.size(), m = 0;
  vector <ll> ans(n, 0);
  while (m < n && a[m] == 0) m++;
  if (k && m && (k >= n || k * m >= n)) return ans;
  if (m == n) return ans[0] = 1, ans;
  ll lead = m * k;
  vector <ll> b(a.begin() + m, a.end());
  ll base = mpow(b[0], k), inv = mpow(b[0], mod - 2);
  for (int i = 0; i < n - m; ++i)
    b[i] = mul(b[i], inv);
  b = Ln(b);
  for (int i = 0; i < n - m; ++i)
    b[i] = mul(b[i], k % mod);
  b = Exp(b);
  for (int i = lead; i < n; ++i)
    ans[i] = mul(b[i - lead], base);
  return ans;
}
vector <ll> Evaluate(vector <ll> a, vector <ll> x) {
  if (x.empty()) return {};
  int n = x.size();
  vector <vector <ll>> up(n * 2);
  for (int i = 0; i < n; ++i)
    up[i + n] = {sub(0, x[i]), 1};
  for (int i = n - 1; i > 0; --i)
    up[i] = Mul(up[i * 2], up[i * 2 + 1]);
  vector <vector <ll>> down(n * 2);
  down[1] = Divide(a, up[1]).second;
  for (int i = 2; i < n * 2; ++i)
    down[i] = Divide(down[i >> 1], up[i]).second;
  vector <ll> y(n);
  for (int i = 0; i < n; ++i) y[i] = down[i + n][0];
  return y;
}
vector <ll> Interpolate(vector <ll> x, vector <ll> y) {
  int n = x.size();
  vector <vector <ll>> up(n * 2);
  for (int i = 0; i < n; ++i)
    up[i + n] = {sub(0, x[i]), 1};
  for (int i = n - 1; i > 0; --i)
    up[i] = Mul(up[i * 2], up[i * 2 + 1]);
  vector <ll> a = Evaluate(Derivative(up[1]), x);
  for (int i = 0; i < n; ++i)
    a[i] = mul(y[i], mpow(a[i], mod - 2));
  vector <vector <ll>> down(n * 2);
  for (int i = 0; i < n; ++i) down[i + n] = {a[i]};
  for (int i = n - 1; i > 0; --i) {
    vector <ll> lhs = Mul(down[i * 2], up[i * 2 + 1]);
    vector <ll> rhs = Mul(down[i * 2 + 1], up[i * 2]);
    down[i].resize(lhs.size());
    for (int j = 0; j < lhs.size(); ++j)
      down[i][j] = add(lhs[j], rhs[j]);
  }
  return down[1];
}
vector <ll> TaylorShift(vector <ll> a, ll c) {
  // return sum a_i(x + c)^i;
  // fac[i] = i!, facp[i] = inv(i!)
  int n = a.size();
  for (int i = 0; i < n; ++i) a[i] = mul(a[i], fac[i]);
  reverse(all(a));
  vector <ll> b(n);
  ll w = 1;
  for (int i = 0; i < n; ++i)
    b[i] = mul(facp[i], w), w = mul(w, c);
  a = Mul(a, b, n), reverse(all(a));
  for (int i = 0; i < n; ++i) a[i] = mul(a[i],facp[i]);
  return a;
}
vector <ll> SamplingShift(vector <ll> a, ll c, int m) {
  // given f(0), f(1), ..., f(n - 1)
  // return f(c), f(c + 1), ..., f(c + m - 1)
  int n = a.size();
  for (int i = 0; i < n; ++i) a[i] = mul(a[i],facp[i]);
  vector <ll> b(n);
  for (int i = 0; i < n; ++i) {
    b[i] = facp[i];
    if (i & 1) b[i] = sub(0, b[i]);
  }
  a = Mul(a, b, n);
  for (int i = 0; i < n; ++i) a[i] = mul(a[i], fac[i]);
  reverse(all(a));
  ll w = 1;
  for (int i = 0; i < n; ++i)
    b[i] = mul(facp[i], w), w = mul(w, sub(c, i));
  a = Mul(a, b, n);
  reverse(all(a));
  for (int i = 0; i < n; ++i) a[i] = mul(a[i],facp[i]);
  a.resize(m), b.resize(m);
  for (int i = 0; i < m; ++i) b[i] = facp[i];
  a = Mul(a, b, m);
  for (int i = 0; i < m; ++i) a[i] = mul(a[i], fac[i]);
  return a;
}