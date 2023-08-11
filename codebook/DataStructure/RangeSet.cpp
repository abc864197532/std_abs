struct RangeSet { // [l, r)
  set <pii> S;
  void cut(int x) {
    auto it = S.lower_bound({x + 1, -1});
    if (it == S.begin()) return;
    auto [l, r] = *prev(it);
    if (l >= x || x >= r) return;
    S.erase(prev(it));
    S.insert({l, x});
    S.insert({x, r});
  }
  vector <pii> split(int l, int r) {
    // remove and return ranges in [l, r)
    cut(l), cut(r);
    vector <pii> res;
    while (true) {
      auto it = S.lower_bound({l, -1});
      if (it == S.end() || r <= it->first) break;
      res.pb(*it), S.erase(it);
    }
    return res;
  }
  void insert(int l, int r) {
    // add a range [l, r), [l, r) not in S
    auto it = S.lower_bound({l, r});
    if (it != S.begin() && prev(it)->second == l)
      l = prev(it)->first, S.erase(prev(it));
    if (it != S.end() && r == it->first)
      r = it->second, S.erase(it);
    S.insert({l, r});
  }
  bool count(int x) {
    auto it = S.lower_bound({x + 1, -1});
    return it != S.begin() && prev(it)->first <= x
            && x < prev(it)->second;
  }
};