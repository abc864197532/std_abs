vector <pair <int, long long>> adj[N];
template <typename T>
struct NegativeCycle {
  vector <T> dis;
  vector <int> rt;
  int n; T INF;
  vector <int> cycle;
  NegativeCycle () = default;
  NegativeCycle (int _n) : n(_n), INF(numeric_limits<T>::max()) {
    dis.assign(n, 0), rt.assign(n, -1);
    int relax = -1;
    for (int t = 0; t < n; ++t) {
      relax = -1;
      for (int i = 0; i < n; ++i) {
        for (auto [j, w] : adj[i]) if (dis[j] > dis[i] + w) {
          dis[j] = dis[i] + w, rt[j] = i;
          relax = j;
        }
      }
    }
    if (relax != -1) {
      int s = relax;
      for (int i = 0; i < n; ++i) s = rt[s];
      vector <bool> vis(n, false);
      while (!vis[s]) {
        cycle.push_back(s), vis[s] = true;
        s = rt[s];
      }
      reverse(cycle.begin(), cycle.end());
    }
  }
};