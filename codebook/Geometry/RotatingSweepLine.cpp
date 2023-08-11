void RotatingSweepLine(vector <Pt> &pt) {
  int n = pt.size();
  vector <int> ord(n), cur(n);
  vector <pii> line;
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) if (i ^ j)
      line.emplace_back(i, j);
  sort(all(line), [&](pii i, pii j) {
    Pt a = pt[i.second] - pt[i.first];
    Pt b = pt[j.second] - pt[j.first];
    if (pos(a) == pos(b)) return sign(a ^ b) > 0;
    return pos(a) < pos(b);
  });
  iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) {
    return (sign(pt[i].y - pt[j].y) == 0 ? pt[i].x < pt[j].x : pt[i].y < pt[j].y);
  });
  for (int i = 0; i < n; ++i) cur[ord[i]] = i;
  for (auto [i, j] : line) {
    // point sort by the distance to line(i, j)
    tie(cur[i], cur[j], ord[cur[i]], ord[cur[j]]) = make_tuple(cur[j], cur[i], j, i);
  }
}