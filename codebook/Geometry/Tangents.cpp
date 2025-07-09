auto circle_point_tangent(Cir c, Pt p) { // 6af9a8
  vector<Line> res;
  double d_sq = abs2(p - c.o);
  if (sign(d_sq - c.r * c.r) == 0) {
    res.pb({p, p + perp(p - c.o)});
  } else if (d_sq > c.r * c.r) {
    double s = d_sq - c.r * c.r;
    Pt v = p + (c.o - p) * s / d_sq;
    Pt u = perp(c.o - p) * sqrt(s) * c.r / d_sq;
    res.pb({p, v + u});
    res.pb({p, v - u});
  }
  return res;
}
auto circles_tangent(Cir c1, Cir c2, int sign1) { // b8d41e
  // sign1 = 1 for outer tang, -1 for inter tang
  vector<Line> res;
  double d_sq = abs2(c1.o - c2.o);
  if (sign(d_sq) == 0) return res;
  double d = sqrt(d_sq);
  Pt v = (c2.o - c1.o) / d;
  double c = (c1.r - sign1 * c2.r) / d;
  if (c * c > 1) return res;
  double h = sqrt(max(0.0, 1.0 - c * c));
  for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
    Pt n = Pt(v.x * c - sign2 * h * v.y, v.y * c + sign2 * h * v.x);
    Pt p1 = c1.o + n * c1.r;
    Pt p2 = c2.o + n * (c2.r * sign1);
    if (sign(p1.x - p2.x) == 0 && sign(p1.y - p2.y) == 0)
      p2 = p1 + perp(c2.o - c1.o);
    res.pb({p1, p2});
  }
  return res;
}
/* The point should be strictly out of hull
  return arbitrary point on the tangent line */
pii point_convex_tengent(vector<Pt> &C, Pt p) {//63a82a
  auto gao = [&](int s) {
    return cyc_tsearch(sz(C), [&](int x, int y)
    { return ori(p, C[x], C[y]) == s; });
  };
  return pii(gao(1), gao(-1));
} // return (a, b), ori(p, C[a], C[b]) >= 0