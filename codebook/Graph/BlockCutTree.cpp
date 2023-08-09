vector <int> g[N], _g[N << 1];
// _g: index >= N: bcc, index < N: original vertex
// Notice Isolated Point
int pa[N], dep[N], low[N], _id;
bool vis[N], is_cut[N];
vector <int> stk, bcc[N];
void add_edge(int u, int v){_g[u].pb(v),_g[v].pb(u);}
void dfs(int i, int p = -1) {
  int ch = 0;
  dep[i] = low[i] = ~p ? dep[p] + 1 : 0;
  stk.pb(i), pa[i] = p, vis[i] = true;
  for (int j : g[i]) if (j != p) {
    if (!vis[j]) {
      dfs(j, i), low[i] = min(low[i], low[j]);
      if (low[j] >= dep[i]) {
        is_cut[i] = true;
        int id = _id++, x;
        do {
          x = stk.back(), stk.pop_back();
          bcc[id].pb(x), add_edge(id + N, x);
        } while (x != j);
        bcc[id].pb(i), add_edge(id + N, i);
      }
    } else low[i] = min(low[i], dep[j]);
  }
  if (p == -1 && ch < 2) is_cut[i] = false;
}
int pa2[N << 1], dep2[N << 1];
void dfs2(int i, int p = -1) {
  dep2[i] = ~p ? dep2[p] + 1 : 0, pa2[i] = p;
  for (int j : _g[i]) if (j != p) {
    dfs2(j, i);
  }
}
int bcc_id(int u, int v) {
  if (dep2[u] < dep2[v]) swap(u, v);
  return pa2[u] - N;
}
void build(int n) {
  for (int i = 0; i < n; ++i) if (!vis[i])
    dfs(i), dfs2(i);
}