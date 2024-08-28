struct HopcroftKarp { // 0-based, remember to init
  const int INF = 1 << 30;
  vector <vector <int>> g;
  vector <int> match, dis, matched, vis;
  int n, m;
  bool dfs(int x) {
    vis[x] = true;
    for (int y : g[x])
      if (match[y] == -1 || (dis[match[y]] == dis[x] + 1 && !vis[match[y]] && dfs(match[y]))) {
        match[y] = x, matched[x] = true;
        return true;
      }
    return false;
  }
  bool bfs() {
    fill(all(dis), -1);
    queue <int> q;
    for (int x = 0; x < n; ++x) if (!matched[x])
      dis[x] = 0, q.push(x);
    int mx = INF;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int y : g[x]) {
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
    fill(all(match), -1);
    fill(all(matched), 0);
    while (bfs()) {
      fill(all(vis), 0);
      for (int x = 0; x < n; ++x) if (!matched[x])
        res += dfs(x);
    }
    return res;
  }
  void init(int _n, int _m) {
    n = _n, m = _m;
    g.assign(n, vector <int>());
    match.resize(m), dis.resize(n);
    matched.resize(n), vis.resize(n);
  }
  void add_edge(int x, int y) { g[x].pb(y); }
};