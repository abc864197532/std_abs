struct HopcroftKarp { // 0-based
  int n, m;
  vector <vector <int>> g;
  vector <int> l, r, d;
  bool dfs(int x) {
    for (int y : g[x]) if (r[y] == -1 ||
      (d[r[y]] == d[x] + 1 && dfs(r[y])))
      return l[x] = y, r[y] = x, d[x] = -1, true;
    return d[x] = -1, false;
  }
  bool bfs() {
    d.assign(n, -1);
    queue <int> q;
    for (int x = 0; x < n; ++x) if (l[x] == -1)
      d[x] = 0, q.push(x);
    bool good = false;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int y : g[x])
        if (r[y] == -1) good = true;
        else if (d[r[y]] == -1) 
          d[r[y]] = d[x] + 1, q.push(r[y]);
    }
    return good;
  }
  int solve() {
    int res = 0;
    l.assign(n, -1), r.assign(m, -1);
    while (bfs())
      for (int x = 0; x < n; ++x) if (l[x] == -1)
        res += dfs(x);
    return res;
  }
  void add_edge(int x, int y) { g[x].pb(y); }
  HopcroftKarp (int _n, int _m) : n(_n), m(_m), g(n) {}
};