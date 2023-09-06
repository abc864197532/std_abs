struct HopcroftKarp { // 0-based
  const int INF = 1 << 30;
  vector<int> adj[N];
  int match[N], dis[N], v, n, m;
  bool matched[N], vis[N];
  bool dfs(int x) {
    vis[x] = true;
    for (int y : adj[x])
      if (match[y] == -1 || (dis[match[y]] == dis[x] + 1 && !vis[match[y]] && dfs(match[y]))) {
        match[y] = x, matched[x] = true;
        return true;
      }
    return false;
  }
  bool bfs() {
    memset(dis, -1, sizeof(int) * n);
    queue<int> q;
    for (int x = 0; x < n; ++x) if (!matched[x])
      dis[x] = 0, q.push(x);
    int mx = INF;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int y : adj[x]) {
        if (match[y] == -1) {
          mx = dis[x];
          break;
        } else if (dis[match[y]] == -1)
          dis[match[y]] = dis[x] + 1, q.push(match[y]);
      }
    }
    return mx < INF;
  }
  int solve() {
    int res = 0;
    memset(match, -1, sizeof(int) * m);
    memset(matched, 0, sizeof(bool) * n);
    while (bfs()) {
      memset(vis, 0, sizeof(bool) * n);
      for (int x = 0; x < n; ++x) if (!matched[x])
        res += dfs(x);
    }
    return res;
  }
  void init(int _n, int _m) {
    n = _n, m = _m;
    for (int i = 0; i < n; ++i) adj[i].clear();
  }
  void add_edge(int x, int y) {
    adj[x].pb(y);
  }
};