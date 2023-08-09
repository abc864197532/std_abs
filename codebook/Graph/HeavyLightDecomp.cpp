vector <int> g[N];
int dep[N], pa[N], sz[N], ch[N], hd[N], id[N], _id;
void dfs(int i, int p) {
  dep[i] = ~p ? dep[p] + 1 : 0;
  pa[i] = p, sz[i] = 1, ch[i] = -1;
  for (int j : g[i]) if (j != p) {
    dfs(j, i);
    if (ch[i] == -1 || sz[ch[i]] < sz[j]) ch[i] = j;
    sz[i] += sz[j];
  }
}
void hld(int i, int p, int h) {
  hd[i] = h;
  id[i] = _id++;
  if (~ch[i]) hld(ch[i], i, h);
  for (int j : g[i]) if (j != p && j != ch[i])
    hld(j, i, j);
}
void query(int i, int j) {
  // query2 -> [l, r)
  while (hd[i] != hd[j]) {
    if (dep[hd[i]] < dep[hd[j]]) swap(i, j);
    query2(id[hd[i]], id[i] + 1), i = pa[hd[i]];
  }
  if (dep[i] < dep[j]) swap(i, j);
  query2(id[j], id[i] + 1);
}