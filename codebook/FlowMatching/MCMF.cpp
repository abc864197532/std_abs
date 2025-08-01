template <typename T1, typename T2>
struct MCMF { // T1 -> flow, T2 -> cost, 0-based
  const T1 INF1 = numeric_limits<T1>::max() / 2;
  const T2 INF2 = numeric_limits<T2>::max() / 2;
  struct edge { int v; T1 f; T2 c; };
  int n, s, t;
  vector <vector <int>> g;
  vector <edge> e;
  vector <T2> dis, pot;
  vector <int> rt, vis;
  // bool DAG()...
  bool SPFA() {
    rt.assign(n, -1), dis.assign(n, INF2);
    vis.assign(n, false);
    queue <int> q;
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      vis[v] = false;
      for (int id : g[v]) {
        auto [u, f, c] = e[id];
        T2 ndis = dis[v] + c + pot[v] - pot[u];
        if (f > 0 && dis[u] > ndis) {
          dis[u] = ndis, rt[u] = id;
          if (!vis[u]) vis[u] = true, q.push(u);
        }
      }
    }
    return dis[t] != INF2;
  } // a5dc32
  bool dijkstra() {
    rt.assign(n, -1), dis.assign(n, INF2);
    priority_queue <pair <T2, int>, vector <pair <T2, int>>, greater <pair <T2, int>>> pq;
    dis[s] = 0, pq.emplace(dis[s], s);
    while (!pq.empty()) {
      auto [d, v] = pq.top(); pq.pop();
      if (dis[v] < d) continue;
      for (int id : g[v]) {
        auto [u, f, c] = e[id];
        T2 ndis = dis[v] + c + pot[v] - pot[u];
        if (f > 0 && dis[u] > ndis) {
          dis[u] = ndis, rt[u] = id;
          pq.emplace(ndis, u);
        }
      }
    }
    return dis[t] != INF2;
  } // d46baf
  vector <pair <T1, T2>> solve(int _s, int _t) {
    s = _s, t = _t, pot.assign(n, 0);
    vector <pair <T1, T2>> ans; bool fr = true;
    while ((fr ? SPFA() : SPFA())) {
      for (int i = 0; i < n; i++)
        dis[i] += pot[i] - pot[s];
      T1 add = INF1;
      for (int i = t; i != s; i = e[rt[i] ^ 1].v)
        add = min(add, e[rt[i]].f);
      for (int i = t; i != s; i = e[rt[i] ^ 1].v)
        e[rt[i]].f -= add, e[rt[i] ^ 1].f += add;
      ans.emplace_back(add, dis[t]), fr = false;
      for (int i = 0; i < n; ++i) swap(dis[i], pot[i]);
    }
    return ans;
  }
  void add_edge(int u, int v, T1 f, T2 c) {
    g[u].pb(sz(e)), e.pb({v, f, c});
    g[v].pb(sz(e)), e.pb({u, 0, -c});
  }
  MCMF (int _n) : n(_n), g(n), e() {} // 337601
//void reset() {
//  for (int i = 0; i < sz(e); ++i) e[i].f = 0;
//}
};