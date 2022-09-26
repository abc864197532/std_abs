template <typename T>
struct SW { // 0-based
  T g[N][N], sum[N]; int n;
  bool vis[N], dead[N];
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) fill(g[i], g[i] + n, 0);
    fill(dead, dead + n, false);
  }
  void add_edge(int u, int v, T w) {
    g[u][v] += w, g[v][u] += w;
  }
  T solve() {
    T ans = 1 << 30;
    for (int round = 0; round + 1 < n; ++round) {
      fill(vis, vis + n, false), fill(sum, sum + n, 0);
      int num = 0, s = -1, t = -1;
      while (num < n - round) {
        int now = -1;
        for (int i = 0; i < n; ++i) if (!vis[i] && !dead[i]) {
            if (now == -1 || sum[now] < sum[i]) now = i;
          }
        s = t, t = now;
        vis[now] = true, num++;
        for (int i = 0; i < n; ++i) if (!vis[i] && !dead[i]) {
            sum[i] += g[now][i];
          }
      }
      ans = min(ans, sum[t]);
      for (int i = 0; i < n; ++i) {
        g[i][s] += g[i][t];
        g[s][i] += g[t][i];
      }
      dead[t] = true;
    }
    return ans;
  }
};