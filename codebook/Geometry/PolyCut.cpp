vector<Pt> cut(vector<Pt> poly, Pt s, Pt e) {
  vector<Pt> res;
  for (int i = 0; i < sz(poly); ++i) {
    Pt cur = poly[i], prv = i ? poly[i - 1] : poly.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0))
      res.pb(lines_intersect({s, e}, {cur, prv}));
    if (side) res.pb(cur);
  }
  return res;
}