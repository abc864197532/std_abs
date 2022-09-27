const int N = 1 << 20, mod = 998244353, G = 3;
void run (vector <ll> &P, bool inv = false) {
    int N = P.size();
    const ll w = modpow(G, (mod - 1) / N);
    int lg = __lg(N);
    vector <int> rev(N);
    for (int i = 1; i < N; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        if (i < rev[i])
            swap(P[i], P[rev[i]]);
    }
    vector <ll> ws = {inv ? modpow(w, mod - 2) : w};
    for (int i = 1; i < lg; ++i) ws.push_back(ws.back() * ws.back() % mod);
    reverse(ws.begin(), ws.end());
    for (int i = 0; i < lg; ++i) {
        for (int k = 0; k < N; k += (2 << i)) {
            ll base = 1;
            for (int j = k; j < k + (1 << i); ++j, base = base * ws[i] % mod) {
                ll t = base * P[j + (1 << i)] % mod, u = P[j];
                P[j] = u + t, P[j + (1 << i)] = u - t;
                if (P[j] >= mod) P[j] -= mod;
                if (P[j + (1 << i)] < 0) P[j + (1 << i)] += mod;
            }
        }
    }
    if (inv) {
        ll ninv = modpow(N, mod - 2);
        for (int i = 0; i < N; ++i) {
            P[i] = P[i] * ninv % mod;
        }
    }
}