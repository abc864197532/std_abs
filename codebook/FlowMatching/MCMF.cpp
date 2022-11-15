template <typename T>
struct MCMF {
  const T INF = 1ll << 60;
  struct edge {
    int v;
    T f, c;
    edge (int _v, T _f, T _c) : v(_v), f(_f), c(_c) {}
  };
  vector <edge> E;
  vector <vector <int>> adj;
  vector <T> dis, pot;
  vector <int> rt;
  int n, s, t;
  MCMF (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
    adj.resize(n);
  }
  void add_edge(int u, int v, T f, T c) {
    adj[u].pb(E.size()), E.pb(edge(v, f, c));
    adj[v].pb(E.size()), E.pb(edge(u, 0, -c));
  }
  bool SPFA() {
    rt.assign(n, -1), dis.assign(n, INF);
    vector <bool> vis(n, false);
    queue <int> q;
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      vis[v] = false;
      for (int id : adj[v]) if (E[id].f > 0 && dis[E[id].v] > dis[v] + E[id].c + pot[v] - pot[E[id].v]) {
          dis[E[id].v] = dis[v] + E[id].c + pot[v] - pot[E[id].v], rt[E[id].v] = id;
          if (!vis[E[id].v]) vis[E[id].v] = true, q.push(E[id].v);
        }
    }
    return dis[t] != INF;
  }
  bool dijkstra() {
    rt.assign(n, -1), dis.assign(n, INF);
    priority_queue <pair <T, int>, vector <pair <T, int>>, greater <pair <T, int>>> pq;
    dis[s] = 0, pq.emplace(dis[s], s);
    while (!pq.empty()) {
      int d, v; tie(d, v) = pq.top(); pq.pop();
      if (dis[v] < d) continue;
      for (int id : adj[v]) if (E[id].f > 0 && dis[E[id].v] > dis[v] + E[id].c + pot[v] - pot[E[id].v]) {
          dis[E[id].v] = dis[v] + E[id].c + pot[v] - pot[E[id].v], rt[E[id].v] = id;
          pq.emplace(dis[E[id].v], E[id].v);
        }
    }
    return dis[t] != INF;
  }
  pair <T, T> solve() {
    pot.assign(n, 0);
    T cost = 0, flow = 0;
    bool fr = true;
    while ((fr ? SPFA() : dijkstra())) {
      for (int i = 0; i < n; i++) {
        dis[i] += pot[i] - pot[s];
      }
      T add = INF;
      for (int i = t; i != s; i = E[rt[i] ^ 1].v) {
        add = min(add, E[rt[i]].f);
      }
      for (int i = t; i != s; i = E[rt[i] ^ 1].v) {
        E[rt[i]].f -= add, E[rt[i] ^ 1].f += add;
      }
      flow += add, cost += add * dis[t];
      fr = false;
      swap(dis, pot);
    }
    return make_pair(flow, cost);
  }
};