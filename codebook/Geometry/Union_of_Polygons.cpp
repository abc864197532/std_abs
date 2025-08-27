// in CCW order, use index as tiebreaker when collinear
auto polys_border(vector<vector<Pt>> poly, int id) {
  auto get = [&](auto &p, int i) {
    return make_pair(p[i], p[(i + 1) % sz(p)]); };
  vector<pair<Pt, Pt>> seg;
  for (int e = 0; e < sz(poly[id]); ++e) {
    auto [s, t] = get(poly[id], e);
    vector<pair<Pt, int>> vec;
    vec.emplace_back(s, -1 << 30);
    vec.emplace_back(t, 1 << 30);
    for (int i = 0; i < sz(poly); ++i) {
      int st = find_if(all(poly[i]), [&](Pt p) {
        return ori(p, s, t) == 1; }) - poly[i].begin();
      if (st == sz(poly[i])) continue;
      for (int j = st; j < st + sz(poly[i]); ++j) {
        auto [a, b] = get(poly[i], j % sz(poly[i]));
        if (same_vec(a - b, s - t, -1)) {
          if (ori(a, b, s) == 0 && same_vec(a - b, s - t, 1) && i <= id) {
            vec.emplace_back(a, -1);
            vec.emplace_back(b, 1);
          }
        } else {
          int s1 = ori(a, s, t) == 1, s2 = ori(b, s, t) == 1;
          if (s1 ^ s2) {
            auto p = lines_intersect({a, b}, {s, t});
            vec.emplace_back(p, s1 ? 1 : -1);
          }
        }
      }
    }
    sort(all(vec), [&](auto i, auto j) {
      return cmp_line(i.first, j.first, s, t); });
    int base = 1 << 30; Pt lst(0, 0);
    for (auto [cur, val] : vec) {
      if (!base) seg.emplace_back(lst, cur);
      lst = cur, base += val;
    }
  }
  return seg;
} // 704477
double polys_union_area(vector<vector<Pt>> poly) {
  double res = 0;
  for (int i = 0; i < sz(poly); ++i) {
    auto seg = polys_border(poly, i);
    for (auto [l, r] : seg) res += l ^ r;
  }
  return res / 2;
} // d055fb