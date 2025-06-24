struct Event {
  Pt d; int u, v;
  bool operator < (const Event &b) const {
    return sign(d ^ b.d) > 0; }
};
Pt ref(Pt o) {return pos(o) == 1 ? Pt(-o.x, -o.y) : o;}
void RotatingSweepLine(vector <Pt> &pt) {
  int n = pt.size();
  vector <int> ord(n), pos(n);
  vector <Event> e;
  for (int i = 0; i < n; ++i) 
    for (int j = i + 1; j < n; ++j) if (i ^ j)
      e.pb({ref(pt[i] - pt[j]), i, j});
  sort(all(e));
  iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) {
    return (sign(pt[i].y - pt[j].y) == 0 ?
        pt[i].x < pt[j].x : pt[i].y < pt[j].y); });
  for (int i = 0; i < n; ++i) pos[ord[i]] = i;
  const auto makeReverse = [](auto &v) {
    sort(all(v)); v.resize(unique(all(v)) - v.begin());
    vector <pii> segs;
    for (int i = 0, j = 0; i < v.size(); i = j) {
      for (;j < v.size() && v[j] - v[i] <= j - i; ++j);
      segs.emplace_back(v[i], v[j - 1] + 1 + 1);
    }
    return segs;
  };
  for (int i = 0, j = 0; i < e.size(); i = j) {
    vector<int> tmp;
    for (; j < e.size() && !(e[i] < e[j]); j++)
      tmp.pb(min(pos[e[j].u], pos[e[j].v]));
    for (auto [l, r] : makeReverse(tmp)) {
      reverse(ord.begin() + l, ord.begin() + r);
      for (int t = l; t < r; ++t) pos[ord[t]] = t;
      // update value here
    }
  }
}