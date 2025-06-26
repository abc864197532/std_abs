// notice identical circles, compare cross -> x if the precision is bad
vector<pair<Pt, Pt>> circles_border(vector<Cir> c, int id) {
  vector<pair<Pt, int>> vec;
  int base = 0;
  for (int i = 0; i < sz(c); ++i) if (id != i) {
    if (sign(c[id].r - c[i].r) < 0 && abs2(c[id].o - c[i].o) <= (c[id].r - c[i].r) * (c[id].r - c[i].r)) base++;
    auto tmp = circles_intersect(c[id], c[i]);
    if (sz(tmp) == 2) {
      Pt l = tmp[0] - c[id].o, r = tmp[1] - c[id].o;
      vec.emplace_back(l, 1);
      vec.emplace_back(r, -1);
      if (cmp(r, l)) base++;
    }
  }
  vec.emplace_back(Pt(-c[id].r, 0), 0);
  sort(all(vec), [&](auto i, auto j) {
    return cmp(i.first, j.first);
  });
  vector<pair<Pt, Pt>> seg;
  Pt v = Pt(c[id].r, 0), lst = v;
  for (auto [cur, val] : vec) {
    if (base == 0) seg.emplace_back(lst, cur);
    lst = cur, base += val;
  }
  if (base == 0) seg.emplace_back(lst, v);
  for (auto &[l, r] : seg)
    l = l + c[id].o, r = r + c[id].o;
  return seg;
}
double circles_union_area(vector<Cir> c) {
  double res = 0;
  for (int i = 0; i < sz(c); ++i) {
    auto seg = circles_border(c, i);
    auto F = [&] (double t) { return c[i].r * (c[i].r * t + c[i].o.x * sin(t) - c[i].o.y * cos(t)); };
    for (auto [l, r] : seg) {
      double tl = theta(l - c[i].o), tr = theta(r - c[i].o);
      if (sign(tl - tr) > 0) tr += PI * 2;
      res += F(tr) - F(tl);
    }
  }
  return res / 2;
}