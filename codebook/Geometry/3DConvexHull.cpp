struct Face {
  int a, b, c;
  Face(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};
auto preprocess(auto pts) {
  auto G = pts.begin();
  vector<int> id;
  auto fail = tuple{-1, -1, -1, id};
  int a = find_if(all(pts), [&](Pt z) {
    return z != *G; }) - G;
  if (a == sz(pts)) return fail;
  int b = find_if(all(pts), [&](Pt z) {
    return cross3(*G, pts[a], z) != Pt(0, 0, 0); }) -G;
  if (b == sz(pts)) return fail;
  int c = find_if(all(pts), [&](Pt z) {
    return sign(volume(*G, pts[a], pts[b], z)) != 0; }) - G;
  if (c == sz(pts)) return fail;
  for (int i = 0; i < sz(pts); i++)
    if (i != a && i != b && i != c) id.pb(i);
  return tuple{a, b, c, id};
}
// return the faces with pts indexes
vector<Face> convex_hull_3D(vector<Pt> pts) {
  int n = sz(pts);
  if (n <= 3) return {}; // be careful about edge case
  vector<Face> now;
  vector<vector<int>> z(n, vector<int>(n));
  auto [a, b, c, ord] = preprocess(pts);
  if (a == -1) return {};
  now.emplace_back(a, b, c); now.emplace_back(c, b, a);
  for (auto i : ord) {
    vector<Face> nxt;
    for (auto &f : now) {
      auto v = volume(pts[f.a], pts[f.b], pts[f.c], pts[i]);
      if (sign(v) <= 0) nxt.pb(f);
      z[f.a][f.b] = z[f.b][f.c] = z[f.c][f.a] = sign(v);
    }
    auto F = [&](int x, int y) {
      if (z[x][y] > 0 && z[y][x] <= 0)
        nxt.emplace_back(x, y, i);
    };
    for (auto &f : now)
      F(f.a, f.b), F(f.b, f.c), F(f.c, f.a);
    now = nxt;
  }
  return now;
}
// n^2 delaunay: facets with negative z normal of
// convexhull of (x, y, x^2 + y^2), use a pseudo-point
// (0, 0, inf) to avoid degenerate case
// test @ SPOJ CH3D
// double area = 0, vol = 0; // surface area / volume
// for (auto [a, b, c]: faces)
//   area += abs(ver(p[a], p[b], p[c]))/2.0,
//   vol += volume(P3(0, 0, 0), p[a], p[b], p[c])/6.0;