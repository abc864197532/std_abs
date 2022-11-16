const int N = 1 << 18, mod = 998244353, G = 3;
struct NTT {
  ll w[N];
  NTT() {
    ll dw = mpow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; ++i) w[i] = w[i - 1] * dw % mod;
  }
  void bitrev(vector<ll>& a, int n) {
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
      for (int k = n >> 1; (i ^= k) < k; k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
  }
  void operator()(vector<ll>& a, int n, bool inv = false) { //0 <= a[i] < P
    bitrev(a, n);
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          ll tmp = mul(a[j + dl], w[x]);
          a[j + dl] = sub(a[j], tmp);
          a[j] = add(a[j], tmp);
        }
      }
    }
    if (inv) {
      reverse(a.begin() + 1, a.end());
      ll invn = mpow(n, mod - 2);
      for (int i = 0; i < n; ++i) a[i] = mul(a[i], invn);
    }
  }
};
vector<ll> mul(vector<ll> a, vector<ll> b, int M = N / 2){
  int m = a.size() + b.size() - 1, n = 1;
  while(n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a, n), ntt(b, n);
  for(int i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);
  ntt(a, n, 1);
  a.resize(min(m, M));
  return a;
}