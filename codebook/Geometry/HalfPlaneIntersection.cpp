vector <Pt> HalfPlaneInter(vector <pair <Pt, Pt>> vec) {
  //          x
  // first -------> second
  auto pos = [&](Pt a) {return sign(a.y) == 0 ?  sign(a.x) < 0 : sign(a.y) > 0;};
  sort(all(vec), [&](pair <Pt, Pt> a, pair <Pt, Pt> b) {
    Pt A = a.second - a.first, B = b.second - b.first;
    if (pos(A) == pos(B)) {
      if (sign(A ^ B) == 0) return sign((b.first - a.first) * (b.second - a.first)) > 0;
      return sign(A ^ B) > 0;
    }
    return pos(A) < pos(B);
  });
  deque <Pt> inter;
  deque <pair <Pt, Pt>> seg;
  int n = vec.size();
  auto get = [&](pair <Pt, Pt> a, pair <Pt, Pt> b) {return intersect(a.first, a.second, b.first, b.second);};
  for (int i = 0; i < n; ++i) if (!i || vec[i] != vec[i - 1]) {
    while (seg.size() >= 2 && sign((vec[i].second - inter.back()) ^ (vec[i].first - inter.back())) == 1) seg.pop_back(), inter.pop_back();
    while (seg.size() >= 2 && sign((vec[i].second - inter.front()) ^ (vec[i].first - inter.front())) == 1) seg.pop_front(), inter.pop_front();
    seg.push_back(vec[i]);
    if (seg.size() >= 2) inter.pb(get(seg[seg.size() - 2], seg.back()));
  }
  while (seg.size() >= 2 && sign((seg.front().second - inter.back()) ^ (seg.front().first - inter.back())) == 1) seg.pop_back(), inter.pop_back();
  inter.push_back(get(seg.front(), seg.back()));
  return vector <Pt>(all(inter));
}