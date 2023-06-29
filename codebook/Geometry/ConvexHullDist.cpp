double ConvexHullDist(vector<Pt> A, vector<Pt> B) {
  for (auto &p : B) p = Pt(0, 0) - p;
  auto C = Minkowski(A, B); // assert SZ(C) > 0
  if (PointInConvex(C, Pt(0, 0))) return 0;
  double ans = PointSegDist(C.back(), C[0], Pt(0, 0));
  for (int i = 0; i + 1 < C.size(); ++i) {
    ans = min(ans, PointSegDist(C[i], C[i + 1], Pt(0, 0)));
  }
  return ans;
}