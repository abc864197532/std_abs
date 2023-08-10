vector <int> g[N], _g[N << 1];
// _g: index >= N: bcc, index < N: original vertex
int pa[N], dep[N], low[N], _id;
bool vis[N];
vector <int> stk;
void dfs(int i, int p = -1) {
  dep[i] = low[i] = ~p ? dep[p] + 1 : 0;
  stk.pb(i), pa[i] = p, vis[i] = true;
  for (int j : g[i]) if (j != p) {
    if (!vis[j]) {
      dfs(j, i), low[i] = min(low[i], low[j]);
      if (low[j] >= dep[i]) {
        int id = _id++, x;
        do {
          x = stk.back(), stk.pop_back();
          _g[id + N].pb(x), _g[x].pb(id + N);
        } while (x != j);
        _g[id + N].pb(i), _g[i].pb(id + N);
      }
    } else low[i] = min(low[i], dep[j]);
  }
}
bool is_cut(int x) {return _g[x].size() != 1;}
vector <int> bcc(int x) {return _g[x + N];}
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