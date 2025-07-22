template <typename T>
struct SW { // 0-based
  const T INF = numeric_limits<T>::max() / 2;
  vector <vector <T>> g;
  vector <T> sum;
  vector <bool> vis, dead;
  int n;
  T solve() {
    T ans = INF;
    for (int r = 0; r + 1 < n; ++r) {
      vis.assign(n, 0), sum.assign(n, 0);
      int num = 0, s = -1, t = -1;
      while (num < n - r) {
        int now = -1;
        for (int i = 0; i < n; ++i)
          if (!vis[i] && !dead[i] && 
            (now == -1 || sum[now] > sum[i])) now = i;
        s = t, t = now;
        vis[now] = true, num++;
        for (int i = 0; i < n; ++i)
          if (!vis[i] && !dead[i]) sum[i] += g[now][i];
      }
      ans = min(ans, sum[t]);
      for (int i = 0; i < n; ++i)
        g[i][s] += g[i][t], g[s][i] += g[t][i];
      dead[t] = true;
    }
    return ans;
  }
  void add_edge(int u, int v, T w) {
    g[u][v] += w, g[v][u] += w; }
  SW (int _n) : n(_n), g(n, vector <T>(n)), dead(n) {}
};