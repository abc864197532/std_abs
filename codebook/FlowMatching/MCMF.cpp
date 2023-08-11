template <typename T1, typename T2>
struct MCMF { // T1 -> flow, T2 -> cost, 0-based
  const T1 INF1 = 1 << 30;
  const T2 INF2 = 1 << 30;
  struct edge {
    int v; T1 f; T2 c;
  } E[M << 1];
  vector <int> adj[N];
  T2 dis[N], pot[N];
  int rt[N], vis[N], n, m, s, t;
  // bool DAG()...
  bool SPFA() {
    fill_n(rt, n, -1), fill_n(dis, n, INF2);
    fill_n(vis, n, false);
    queue <int> q;
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      vis[v] = false;
      for (int id : adj[v]) {
        auto [u, f, c] = E[id];
        T2 ndis = dis[v] + c + pot[v] - pot[u];
        if (f > 0 && dis[u] > ndis) {
          dis[u] = ndis, rt[u] = id;
          if (!vis[u]) vis[u] = true, q.push(u);
        }
      }
    }
    return dis[t] != INF2;
  }
  bool dijkstra() {
    fill_n(rt, n, -1), fill_n(dis, n, INF2);
    priority_queue <pair <T2, int>, vector <pair <T2, int>>, greater <pair <T2, int>>> pq;
    dis[s] = 0, pq.emplace(dis[s], s);
    while (!pq.empty()) {
      auto [d, v] = pq.top(); pq.pop();
      if (dis[v] < d) continue;
      for (int id : adj[v]) {
        auto [u, f, c] = E[id];
        T2 ndis = dis[v] + c + pot[v] - pot[u];
        if (f > 0 && dis[u] > ndis) {
          dis[u] = ndis, rt[u] = id;
          pq.emplace(ndis, u);
        }
      }
    }
    return dis[t] != INF2;
  }
  pair <T1, T2> solve(int _s, int _t) {
    s = _s, t = _t, fill_n(pot, n, 0);
    T1 flow = 0; T2 cost = 0; bool fr = true;
    while ((fr ? SPFA() : dijkstra())) {
      for (int i = 0; i < n; i++)
        dis[i] += pot[i] - pot[s];
      T1 add = INF1;
      for (int i = t; i != s; i = E[rt[i] ^ 1].v)
        add = min(add, E[rt[i]].f);
      for (int i = t; i != s; i = E[rt[i] ^ 1].v)
        E[rt[i]].f -= add, E[rt[i] ^ 1].f += add;
      flow += add, cost += add * dis[t], fr = false;
      for (int i = 0; i < n; ++i) swap(dis[i], pot[i]);
    }
    return make_pair(flow, cost);
  }
  void init(int _n) {
    n = _n, m = 0;
    for (int i = 0; i < n; ++i) adj[i].clear();
  }
  void reset() {
    for (int i = 0; i < m; ++i) E[i].f = 0;
  }
  void add_edge(int u, int v, T1 f, T2 c) {
    adj[u].pb(m), E[m++] = {v, f, c};
    adj[v].pb(m), E[m++] = {u, 0, -c};
  }
};