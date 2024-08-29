struct HLD { // 0-based, remember to build
  int n, _id;
  vector <vector <int>> g;
  vector <int> dep, pa, tsz, ch, hd, id;
  void dfs(int v, int p) {
    dep[v] = ~p ? dep[p] + 1 : 0;
    pa[v] = p, tsz[v] = 1, ch[v] = -1;
    for (int u : g[v]) if (u != p) {
      dfs(u, v);
      if (ch[v] == -1 || tsz[ch[v]] < tsz[u]) 
        ch[v] = u;
      tsz[v] += tsz[u];
    }
  }
  void hld(int v, int p, int h) {
    hd[v] = h, id[v] = _id++;
    if (~ch[v]) hld(ch[v], v, h);
    for (int u : g[v]) if (u != p && u != ch[v])
      hld(u, v, u);
  }
  vector <pii> query(int u, int v) {
    vector <pii> ans;
    while (hd[u] != hd[v]) {
      if (dep[hd[u]] > dep[hd[v]]) swap(u, v);
      ans.emplace_back(id[hd[v]], id[v] + 1);
      v = pa[hd[v]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans.emplace_back(id[u], id[v] + 1);
    return ans;
  }
  void build() {
    for (int i = 0; i < n; ++i) if (id[i] == -1)
      dfs(i, -1), hld(i, -1, i);
  }
  void add_edge(int u, int v) {
    g[u].pb(v), g[v].pb(u); }
  HLD (int _n) : n(_n), _id(0), g(n), dep(n), pa(n),
    tsz(n), ch(n), hd(n), id(n, -1) {}
};