struct BipartiteEdgeColoring { // 1-based
  // returns edge coloring in adjacent matrix G
  int col[N][N], G[N][N], n, m;
  int find_col(int x) {
    int c = 1;
    while (col[x][c]) c++;
    return c;
  }
  void dfs(int v, int c1, int c2) {
    if (!col[v][c1]) return col[v][c2] = 0, void(0);
    int u = col[v][c1];
    dfs(u, c2, c1);
    col[v][c1] = 0, col[v][c2] = u, col[u][c2] = v;
  }
  void init(int _n, int _m) {
    n = _n, m = _m;
    for (int i = 1; i <= n + m; ++i) {
      for (int j = 1; j <= n + m; ++j) G[i][j] = 0;
      for (int j = 1; j <= max(n, m); ++j) col[i][j] = 0;
    }
  }
  void solve(vector <pii> edge) { // (l-index, r-index)
    for (auto [u, v] : edge) {
      v += n;
      int c1 = find_col(u), c2 = find_col(v);
      dfs(u, c2, c1);
      col[u][c2] = v, col[v][c2] = u;
    }
    for (int i = 1; i <= n + m; ++i)
      for (int j = 1; j <= max(n, m); ++j)
        if (col[i][j])
          G[i][col[i][j]] = G[col[i][j]][i] = j;
  }
};