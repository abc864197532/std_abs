template <typename T>
struct Dinic { // 0-base
  const T INF = 1 << 30;
  struct edge {
    int to, rev;
    T cap, flow;
  };
  vector<edge> adj[N];
  bool isS[N];
  int s, t, dis[N], cur[N], n;
  T dfs(int u, T cap) {
    if (u == s || !cap) return cap;
    for (int &i = cur[u]; i < adj[u].size(); ++i) {
      edge &e = adj[u][i], &re = adj[e.to][e.rev];
      if (dis[e.to] == dis[u] - 1 && re.flow != re.cap) {
        T df = dfs(e.to, min(re.cap - re.flow, cap));
        if (df) {
          e.flow -= df, re.flow += df;
          return df;
        }
      }
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    fill_n(dis, n, -1);
    queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto &u : adj[v])
        if (!~dis[u.to] && u.flow != u.cap) {
          q.push(u.to);
          dis[u.to] = dis[v] + 1;
        }
    }
    return dis[t] != -1;
  }
  T solve(int _s, int _t) {
    s = _s, t = _t;
    T flow = 0, df;
    while (bfs()) {
      fill_n(cur, n, 0);
      while ((df = dfs(t, INF))) flow += df;
    }
    return flow;
  }
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) adj[i].clear();
  }
  void reset() {
    for (int i = 0; i < n; ++i)
      for (auto &j : adj[i]) j.flow = 0;
  }
  void add_edge(int u, int v, T cap) {
    adj[u].pb(edge{v, (int)adj[v].size(), cap, 0});
    adj[v].pb(edge{u, (int)adj[u].size() - 1, 0, 0});
  }
};