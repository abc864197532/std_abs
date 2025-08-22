// m=0: segment, m=1: ray from l.a to l.b, m=2: line
bool lines_intersect_check(Line l1, int m1, Line l2, int m2, int strict) { // 56cc8d
  auto on = [&](Line l, int m, Pt p) {
    if (ori(l.a, l.b, p) != 0) return false;
    if (m && abs2(l.a - p) > abs2(l.b - p)) return true;
    return m == 2 || sign((p - l.a) * (p - l.b)) <= -strict;
  };
  if (same_vec(l1, l2, 0)) {
    return on(l1, m1, l2.a) || on(l1, m1, l2.b) ||
           on(l2, m2, l1.a) || on(l2, m2, l1.b);
  }
  auto good = [&](Line l, int m, Line o) {
    if (m && abs((l.a - o.a) ^ (l.a - o.b)) > abs((l.b - o.a) ^ (l.b - o.b))) return true;
    return m == 2 || ori(l.a, o.a, o.b) * ori(l.b, o.a, o.b) == -1;
  };
  if (good(l1, m1, l2) && good(l2, m2, l1)) return 1;
  if (!strict) {
    if (m2 != 2 && on(l1, m1, l2.a)) return 1;
    if (m2 == 0 && on(l1, m1, l2.b)) return 1;
    if (m1 != 2 && on(l2, m2, l1.a)) return 1;
    if (m1 == 0 && on(l2, m2, l1.b)) return 1;
  }
  return 0;
}
// notice two lines are parallel
auto lines_intersect(Line a, Line b) { // 726acc
  auto abc = (a.b - a.a) ^ (b.a - a.a);
  auto abd = (a.b - a.a) ^ (b.b - a.a);
  return make_pair((b.b * abc - b.a * abd), abc - abd);
}
// res[0] -> res[1] and l.a -> l.b: same direction
vector<Pt> circle_line_intersect(Cir c, Line l) { // b7bdce
  Pt p = l.a + (l.b - l.a) * ((c.o - l.a) * (l.b - l.a)) / abs2(l.b - l.a);
  double s = (l.b - l.a) ^ (c.o - l.a), h2 = c.r * c.r - s * s / abs2(l.b - l.a);
  if (sign(h2) == -1) return {};
  if (sign(h2) == 0) return {p};
  Pt h = (l.b - l.a) / abs(l.b - l.a) * sqrt(h2);
  return {p - h, p + h};
}
// covered area of c1: arc from res[0] to res[1], CCW 
vector<Pt> circles_intersect(Cir c1, Cir c2) {// 0acf68
  double d2 = abs2(c1.o - c2.o), d = sqrt(d2);
  if (d < max(c1.r, c2.r) - min(c1.r, c2.r) || d > c1.r + c2.r) return {};
  Pt u = (c1.o + c2.o) / 2 + (c1.o - c2.o) * ((c2.r * c2.r - c1.r * c1.r) / (2 * d2));
  double A = sqrt((c1.r + c2.r + d) * (c1.r - c2.r + d) * (c1.r + c2.r - d) * (-c1.r + c2.r + d));
  Pt v = perp(c2.o - c1.o) * A / (2 * d2);
  if (sign(v.x) == 0 && sign(v.y) == 0) return {u};
  return {u - v, u + v};
}
// return edge endpoint, at point -> ids are the same
vector<pii> convex_line_intersect(vector <Pt> &C, Line la) {
  auto dis = [&](int p)
  { return (la.b - la.a) ^ (C[p] - la.a); };
  auto gao = [&](int s) {
    return cyc_tsearch(sz(C), [&](int i, int j)
    { return sign(dis(i) - dis(j)) == s; });
  };
  int x = gao(1), y = gao(-1), n = sz(C);
  if (sign(dis(x)) < 0 || sign(dis(y)) > 0) return {};
  if (sign(dis(x)) == 0 || sign(dis(y)) == 0) {
    int v = ((sign(dis(x)) == 0 ? x : y) + n - 1) % n;
    vector <pii> vec;
    for (int i = 0; i < 3; ++i, v = (v + 1) % n)
      if (sign(dis(v)) == 0) vec.emplace_back(v, v);
    return vec;
  }
  auto get = [&](int l, int r, int s) {
    while ((l + 1) % n != r) {
      int m = ((l + r + (l < r ? 0 : n)) / 2) % n;
      (sign(dis(m)) == s ? l : r) = m;
    }
    if (sign(dis(r)) == 0) return pii(r, r);
    return pii(l, r);
  };
  return {get(x, y, 1), get(y, x, -1)};
}