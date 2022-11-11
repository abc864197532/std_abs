const int N = 1 << 20, mod = 998244353, G = 3;
struct NTT {
  ll w[N];
  ll mpow(ll a, ll n);
  NTT() {
    ll dw = mpow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; ++i) w[i] = w[i - 1] * dw % mod;
  }
  void bitrev(ll *a, int n) {
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
      for (int k = n >> 1; (i ^= k) < k; k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
  }
  void operator()(ll *a, int n, bool inv = false) { //0 <= a[i] < P
    bitrev(a, n);
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          ll tmp = a[j + dl] * w[x] % mod;
          if ((a[j + dl] = a[j] - tmp) < 0) a[j + dl] += mod;
          if ((a[j] += tmp) >= mod) a[j] -= mod;
        }
      }
    }
    if (inv) {
      reverse(a + 1, a + n);
      ll invn = modpow(n, mod - 2);
      for (int i = 0; i < n; ++i) a[i] = a[i] * invn % mod;
    }
  }
};