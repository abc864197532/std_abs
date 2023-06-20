void fwt(vector <int> &a) {
  // and : a[j] += x;
  //     : a[j] -= x;
  // or  : a[j ^ (1 << i)] += y;
  //     : a[j ^ (1 << i)] -= y;
  // xor : a[j] = x - y, a[j ^ (1 << i)] = x + y;
  //     : a[j] = (x - y) / 2, a[j ^ (1 << i)] = (x + y) / 2;
  int n = __lg(a.size());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 1 << n; ++j) if (j >> i & 1) {
      int x = a[j ^ (1 << i)], y = a[j];
      // do something
    }
  }
}
vector<int> subs_conv(vector<int> a, vector<int> b) {
  // c_i = sum_{j & k = 0, j | k = i} a_j * b_k
  int n = __lg(a.size());
  vector<vector<int>> ha(n + 1, vector<int>(1 << n));
  vector<vector<int>> hb(n + 1, vector<int>(1 << n));
  vector<vector<int>> c(n + 1, vector<int>(1 << n));
  for (int i = 0; i < 1 << n; ++i) {
    ha[__builtin_popcount(i)][i] = a[i];
    hb[__builtin_popcount(i)][i] = b[i];
  }
  for (int i = 0; i <= n; ++i) fwt(ha[i]),fwt(hb[i]);
  for (int i = 0; i <= n; ++i)
    for (int j = 0; i + j <= n; ++j)
      for (int k = 0; k < 1 << n; ++k)
        // mind overflow
        c[i + j][k] += ha[i][k] * hb[j][k]; 
  for (int i = 0; i <= n; ++i)
    fwt(c[i], true);
  vector <int> ans(1 << n);
  for (int i = 0; i < 1 << n; ++i)
    ans[i] = c[__builtin_popcount(i)][i];
  return ans;
}