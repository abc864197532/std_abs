struct Dinic {
  const int INF = 1 << 30;
  struct edge {
    int v, f;
    edge (int _v, int _f) : v(_v), f(_f) {}
  };
  vector <vector <int>> adj;
  vector <edge> E;
  vector <int> level;
  int n, s, t;
  Dinic (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {adj.resize(n);}
  void add_edge(int u, int v, int f) {
    adj[u].pb(E.size()), E.pb(edge(v, f));
    adj[v].pb(E.size()), E.pb(edge(u, 0));
  }
  bool bfs() {
    level.assign(n, -1);
    queue <int> q;
    level[s] = 0, q.push(s);
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int id : adj[v]) if (E[id].f > 0 && level[E[id].v] == -1) {
          level[E[id].v] = level[v] + 1;
          q.push(E[id].v);
        }
    }
    return level[t] != -1;
  }
  int dfs(int v, int minf) {
    if (v == t) return minf;
    int ans = 0;
    for (int id : adj[v]) if (E[id].f > 0 && level[E[id].v] == level[v] + 1) {
        int nxtf = dfs(E[id].v, min(minf, E[id].f));
        minf -= nxtf, E[id].f -= nxtf;
        ans += nxtf, E[id ^ 1].f += nxtf;
        if (!minf) return ans;
      }
    if (!ans) level[v] = -1;
    return ans;
  }
  int solve() {
    int ans = 0;
    while (bfs()) ans += dfs(s, INF);
    return ans;
  }
};