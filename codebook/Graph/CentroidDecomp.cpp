vector <int> g[N];
int dis[N][logN], pa[N], sz[N], dep[N];
bool vis[N];
void dfs_sz(int i, int p) {
  sz[i] = 1;
  for (int j : g[i]) if (j != p && !vis[j])
    dfs_sz(j, i), sz[i] += sz[j];
}
int cen(int i, int p, int _n) {
  for (int j : g[i]) if (j != p && !vis[j] && sz[j] > _n / 2)
    return cen(j, i, _n);
  return i;
}
void dfs_dis(int i, int p, int d) {
  // from i to ancestor with depth d
  dis[i][d] = ~p ? dis[p][d] + 1 : 0;
  for (int j : g[i]) if (j != p && !vis[j])
    dfs_dis(j, i, d);
}
void cd(int i, int p, int d) {
  dfs_sz(i, -1), i = cen(i, -1, sz[i]);
  vis[i] = true, pa[i] = p, dep[i] = d;
  dfs_dis(i, -1, d);
  for (int j : g[i]) if (!vis[j])
    cd(j, i, d + 1);
}