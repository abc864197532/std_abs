struct BipartiteEdgeColoring { // 1-based
  // returns edge coloring in adjacent matrix G
  int n, m;
  vector <vector <int>> col, G;
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
  void solve() {
    for (int i = 1; i <= n + m; ++i)
      for (int j = 1; j <= max(n, m); ++j)
        if (col[i][j])
          G[i][col[i][j]] = G[col[i][j]][i] = j;
  } // u = left index, v = right index
  void add_edge(int u, int v) {
    int c1 = find_col(u), c2 = find_col(v + n);
    dfs(u, c2, c1);
    col[u][c2] = v + n, col[v + n][c2] = u;
  }
  BipartiteEdgeColoring (int _n, int _m) : n(_n),
    m(_m), col(n + m + 1, vector <int>(max(n, m) + 1)),
    G(n + m + 1, vector <int>(n + m + 1)) {}
};