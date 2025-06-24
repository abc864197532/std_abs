/* The point should be strictly out of hull
  return arbitrary point on the tangent line */
pii get_tangent(vector<Pt> &C, Pt p) {
  auto gao = [&](int s) {
    return cyc_tsearch(C.size(), [&](int x, int y)
    { return ori(p, C[x], C[y]) == s; });
  };
  return pii(gao(1), gao(-1));
} // return (a, b), ori(p, C[a], C[b]) >= 0