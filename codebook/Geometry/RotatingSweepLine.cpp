void RotatingSweepLine(vector <Pt> &pt) {
  int n = pt.size();
  vector <int> ord(n), pos(n);
  vector <pii> line;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i ^ j)
    line.emplace_back(i, j);
  auto in = [&](Pt a) {return sign(a.y) == 0 ? sign(a.x) < 0 : sign(a.y) > 0;};
  sort(all(line), [&](pii i, pii j) {
    Pt a = pt[i.second] - pt[i.first], b = pt[j.second] - pt[j.first];
    return (in(a) == in(b) ? sign(a ^ b) > 0 : in(a) < in(b));
  });
  iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) {
    return (sign(pt[i].y - pt[j].y) == 0 ? pt[i].x < pt[j].x : pt[i].y < pt[j].y);
  });
  for (int i = 0; i < n; ++i) pos[ord[i]] = i;
  for (auto [i, j] : line) {
    // point sort by the distance to line(i, j)
    tie(pos[i], pos[j], ord[pos[i]], ord[pos[j]]) = make_tuple(pos[j], pos[i], j, i);
  }
}