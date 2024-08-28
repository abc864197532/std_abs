template <typename T1, typename T2>
struct MCMF { // T1 -> flow, T2 -> cost, 0-based, init!
  const T1 INF1 = numeric_limits<T1>::max() / 2;
  const T2 INF2 = numeric_limits<T2>::max() / 2;
  struct edge {
    int v; T1 f; T2 c;
  };
  vector <vector <int>> g;
  vector <edge> e;
  vector <T2> dis, pot;
  vector <int> rt, vis;
  int n, s, t;
  // bool DAG()...
  bool SPFA() {
    fill(all(rt), -1), fill(all(dis), INF2);
    fill(all(vis), false);
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
  }
  bool dijkstra() {
    fill(all(rt), -1), fill(all(dis), INF2);
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
  }
  vector <pair <T1, T2>> solve(int _s, int _t) {
    s = _s, t = _t, fill(all(pot), 0);
    vector <pair <T1, T2>> ans; bool fr = true;
    while ((fr ? SPFA() : dijkstra())) {
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
  void init(int _n) {
    n = _n;
    g.assign(n, vector <int>()), e.clear();
    dis.resize(n), pot.resize(n);
    rt.resize(n), vis.resize(n);
  }
  void reset() {
    for (int i = 0; i < (int)e.size(); ++i) e[i].f = 0;
  }
  void add_edge(int u, int v, T1 f, T2 c) {
    g[u].pb((int)e.size()), e.pb({v, f, c});
    g[v].pb((int)e.size()), e.pb({u, 0, -c});
  }
};