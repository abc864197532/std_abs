struct Vizing { // 1-based
  // returns edge coloring in adjacent matrix G
  int n;
  vector <vector <int>> C, G;
  vector <int> X, vst;
  vector <pii> E;
  void solve() {
    auto update = [&](int u)
    { for (X[u] = 1; C[u][X[u]]; ++X[u]); };
    auto color = [&](int u, int v, int c) {
      int p = G[u][v];
      G[u][v] = G[v][u] = c;
      C[u][c] = v, C[v][c] = u;
      C[u][p] = C[v][p] = 0;
      if (p) X[u] = X[v] = p;
      else update(u), update(v);
      return p;
    };
    auto flip = [&](int u, int c1, int c2) {
      int p = C[u][c1];
      swap(C[u][c1], C[u][c2]);
      if (p) G[u][p] = G[p][u] = c2;
      if (!C[u][c1]) X[u] = c1;
      if (!C[u][c2]) X[u] = c2;
      return p;
    };
    fill(1 + all(X), 1);
    for (int t = 0; t < sz(E); ++t) {
      auto [u, v0] = E[t];
      int v = v0, c0 = X[u], c = c0, d;
      vector<pii> L;
      fill(1 + all(vst), 0);
      while (!G[u][v0]) {
        L.emplace_back(v, d = X[v]);
        if (!C[v][c]) {
          for (int a = sz(L) - 1; a >= 0; --a) 
            c = color(u, L[a].first, c);
        } else if (!C[u][d]) {
          for (int a = sz(L) - 1; a >= 0; --a) 
            color(u, L[a].first, L[a].second);
        } else if (vst[d]) break;
        else vst[d] = 1, v = C[u][d];
      }
      if (!G[u][v0]) {
        for (; v; v = flip(v, c, d), swap(c, d));
        if (int a; C[u][c0]) {
          for (a = sz(L) - 2;
            a >= 0 && L[a].second != c; --a);
          for (; a >= 0; --a)
            color(u, L[a].first, L[a].second);
        }
        else --t;
      }
    }
  }
  void add_edge(int u, int v) { E.emplace_back(u, v); }
  Vizing(int _n) : n(_n), C(n + 1, vector<int>(n + 1)),
  G(n + 1, vector<int>(n + 1)), X(n + 1), vst(n + 1) {}
};