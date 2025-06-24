double ConvexHullDist(vector<Pt> A, vector<Pt> B) {
  Pt O(0, 0);
  for (auto &p : B) p = O - p;
  auto C = Minkowski(A, B); // assert SZ(C) > 0
  if (PointInConvex(C, O)) return 0;
  double ans = PointSegDist(C.back(), C[0], O);
  for (int i = 0; i + 1 < C.size(); ++i)
    ans = min(ans, PointSegDist(C[i], C[i + 1], O));
  return ans;
}