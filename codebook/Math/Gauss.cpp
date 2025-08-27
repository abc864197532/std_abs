auto gauss(vector<vector<int>> a, vector<int> b) {
  // solve ax = b
  int n = sz(a), m = sz(a[0]), rk = 0;
  vector<int> depv, free(m, true);
  for (int i = 0; i < m; ++i) {
    int p = -1;
    for (int j = rk; j < n; ++j)
      if (p == -1 || abs(a[j][i]) > abs(a[p][i]))
        p = j;
    if (p == -1 || a[p][i] == 0) continue;
    swap(a[p], a[rk]), swap(b[p], b[rk]);
    int inv = Pow(a[rk][i], mod - 2);
    for (int &x : a[rk]) x = mul(x, inv);
    b[rk] = mul(b[rk], inv);
    for (int j = 0; j < n; ++j) if (j ^ rk) {
      int x = a[j][i];
      for (int k = 0; k < m; ++k) 
        a[j][k] = sub(a[j][k], mul(x, a[rk][k]));
      b[j] = sub(b[j], mul(x, b[rk]));
    }
    depv.pb(i), free[i] = false, rk++;
  }
  vector<int> x; vector<vector <int>> h;
  for (int i = rk; i < n; ++i) if (b[i] != 0)
    return make_pair(x, h); // not consistent
  x.resize(m);
  for (int i = 0; i < rk; ++i) x[depv[i]] = b[i];
  for (int i = 0; i < m; ++i) if (free[i]) {
    h.emplace_back(m), h.back()[i] = 1;
    for (int j = 0; j < rk; ++j)
      h.back()[depv[j]] = sub(0, a[j][i]);
  }
  return make_pair(x, h); // solution = x + span(h[i])
}