vector<Pt> HalfPlaneInter(vector<Line> vec) {
  //           x
  // line.a -------> line.b
  int n = vec.size();
  sort(all(vec), [&](Line a, Line b) {
    Pt A = a.b - a.a, B = b.b - b.a;
    if (pos(A) == pos(B)) {
      if (sign(A ^ B) == 0) return sign((b.a - a.a) ^ (b.b - a.a)) > 0;
      return sign(A ^ B) > 0;
    }
    return pos(A) < pos(B);
  });
  auto same = [&](Line a, Line b) {
    return sign((a.b - a.a) ^ (b.b - b.a)) == 0 && sign((a.b - a.a) * (b.b - b.a)) > 0;
  };
  deque <Pt> inter;
  deque <Line> seg;
  for (int i = 0; i < n; ++i) if (!i || !same(vec[i - 1], vec[i])) {
    while (seg.size() >= 2 && sign((vec[i].b - inter.back()) ^ (vec[i].a - inter.back())) == 1) seg.pop_back(), inter.pop_back();
    while (seg.size() >= 2 && sign((vec[i].b - inter.front()) ^ (vec[i].a - inter.front())) == 1) seg.pop_front(), inter.pop_front();
    seg.pb(vec[i]);
    if (seg.size() >= 2) inter.pb(LinesInter(seg[seg.size() - 2], seg.back()));
  }
  while (seg.size() >= 2 && sign((seg.front().b - inter.back()) ^ (seg.front().a - inter.back())) == 1) seg.pop_back(), inter.pop_back();
  inter.pb(LinesInter(seg.front(), seg.back()));
  return vector<Pt>(all(inter));
}