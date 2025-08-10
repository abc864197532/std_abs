// need lca, in, out
vector <pii> virtual_tree(vector <int> &v) {
  auto cmp = [&](int x, int y) {return in[x] < in[y];};
  sort(all(v), cmp);
  for (int i = 1; i < sz(v); ++i)
    v.pb(lca(v[i - 1], v[i]));
  sort(all(v), cmp);
  v.resize(unique(all(v)) - v.begin());
  vector <int> stk(1, v[0]);
  vector <pii> res;
  for (int i = 1; i < sz(v); ++i) {
    int x = v[i];
    while (out[stk.back()] < out[x]) stk.pop_back();
    res.emplace_back(stk.back(), x), stk.pb(x);
  }
  return res;
}