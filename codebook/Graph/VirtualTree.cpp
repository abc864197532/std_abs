// need lca
vector <int> _g[N], stk;
int st[N], ed[N];
void solve(vector<int> v) {
  auto cmp = [&](int x, int y) {return st[x] < st[y];};
  sort(all(v), cmp);
  int sz = v.size();
  for (int i = 0; i < sz - 1; ++i)
    v.pb(lca(v[i], v[i + 1]));
  sort(all(v), cmp);
  v.resize(unique(all(v)) - v.begin());
  stk.clear(), stk.pb(v[0]);
  for (int i = 1; i < v.size(); ++i) {
    int x = v[i];
    while (ed[stk.back()] < ed[x]) stk.pop_back();
    _g[stk.back()].pb(x), stk.pb(x);
  }
  // do something
  for (int i : v) _g[i].clear();
}