vector <int> g[N], _g[N];
// Notice Multiple Edges
int pa[N], low[N], dep[N], bcc_id[N], _id;
vector <int> stk, bcc[N];
bool vis[N], is_bridge[N];
void dfs(int i, int p = -1) {
  low[i] = dep[i] = ~p ? dep[p] + 1 : 0;
  stk.pb(i), pa[i] = p, vis[i] = true;
  for (int j : g[i]) if (j != p) {
    if (!vis[j])
      dfs(j, i), low[i] = min(low[i], low[j]);
    else low[i] = min(low[i], dep[j]);
  }
  if (low[i] == dep[i]) {
    if (~p) is_bridge[i] = true; // (i, pa[i])
    int id = _id++, x;
    do {
      x = stk.back(), stk.pop_back();
      bcc_id[x] = id, bcc[id].pb(x);
    } while (x != i);
  }
}
void build(int n) {
  for (int i = 0; i < n; ++i) if (!vis[i])
    dfs(i);
  for (int i = 0; i < n; ++i) if (is_bridge[i]) {
    int u = bcc_id[i], v = bcc_id[pa[i]];
    _g[u].pb(v), _g[v].pb(u);
  }
}