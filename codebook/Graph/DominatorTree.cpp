struct Dominator_tree {
  int n, id;
  vector <vector <int>> adj, radj, bucket;
  vector <int> sdom, dom, vis, rev, par, rt, mn;
  Dominator_tree (int _n) : n(_n), id(0) {
    adj.resize(n), radj.resize(n), bucket.resize(n);
    sdom.resize(n), dom.resize(n, -1), vis.resize(n, -1);
    rev.resize(n), rt.resize(n), mn.resize(n), par.resize(n);
  }
  void add_edge(int u, int v) {adj[u].pb(v);}
  int query(int v, bool x) {
    if (rt[v] == v) return x ? -1 : v;
    int p = query(rt[v], true);
    if (p == -1) return x ? rt[v] : mn[v];
    if (sdom[mn[v]] > sdom[mn[rt[v]]]) mn[v] = mn[rt[v]];
    rt[v] = p;
    return x ? p : mn[v];
  }
  void dfs(int v) {
    vis[v] = id, rev[id] = v;
    rt[id] = mn[id] = sdom[id] = id, id++;
    for (int u : adj[v]) {
      if (vis[u] == -1) dfs(u), par[vis[u]] = vis[v];
      radj[vis[u]].pb(vis[v]);
    }
  }
  void build(int s) {
    dfs(s);
    for (int i = id - 1; ~i; --i) {
      for (int u : radj[i]) {
        sdom[i] = min(sdom[i], sdom[query(u, false)]);
      }
      if (i) bucket[sdom[i]].pb(i);
      for (int u : bucket[i]) {
        int p = query(u, false);
        dom[u] = sdom[p] == i ? i : p;
      }
      if (i) rt[i] = par[i];
    }
    vector <int> res(n, -1);
    for (int i = 1; i < id; ++i) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    }
    for (int i = 1; i < id; ++i) res[rev[i]] = rev[dom[i]];
    res[s] = s;
    dom = res;
  }
};