pair <ll, ll> area_pair(Line a, Line b) 
{ return {(a.b - a.a) ^ (b.a - a.a), (a.b - a.a) ^ (b.b - a.a)}; }
bool isin(Line l0, Line l1, Line l2) {
  // Check inter(l1, l2) strictly in l0
  auto [a02X, a02Y] = area_pair(l0, l2);
  auto [a12X, a12Y] = area_pair(l1, l2);
  if (a12X - a12Y < 0) a12X *= -1, a12Y *= -1;
  return a02Y * a12X - a02X * a12Y > 0; // C^4
}
/* Having solution, check size > 2 */
/* --^-- Line.a --^-- Line.b --^-- */
vector<Line> HalfPlaneInter(vector<Line> arr) {
  sort(all(arr), [&](Line a, Line b) {
    Pt A = a.b - a.a, B = b.b - b.a;
    if (pos(A) != pos(B)) return pos(A) < pos(B);
    if (sign(A ^ B) != 0) return sign(A ^ B) > 0;
    return ori(a.a, a.b, b.b) < 0;
  });
  deque<Line> dq(1, arr[0]);
  auto same = [&](Pt a, Pt b)
  { return sign(a ^ b) == 0 && pos(a) == pos(b); };
  for (auto p : arr) {
    if (same(dq.back().b - dq.back().a, p.b - p.a))
      continue;
    while (sz(dq) >= 2 && !isin(p, dq[sz(dq) - 2], dq.back())) dq.pop_back();
    while (sz(dq) >= 2 && !isin(p, dq[0], dq[1]))
      dq.pop_front();
    dq.pb(p);
  }
  while (sz(dq) >= 3 && !isin(dq[0], dq[sz(dq) - 2], dq.back())) dq.pop_back();
  while (sz(dq) >= 3 && !isin(dq.back(), dq[0], dq[1]))
    dq.pop_front();
  return vector<Line>(all(dq));
}