double polyUnion(vector <vector <Pt>> poly) {
  int n = poly.size();
  double ans = 0;
  auto solve = [&](Pt a, Pt b, int cid) {
    vector <pair <Pt, int>> event;
    for (int i = 0; i < n; ++i) {
      int st = 0, sz = poly[i].size();
      while (st < sz && ori(poly[i][st], a, b) != 1)
        st++;
      if (st == sz) continue;
      for (int j = 0; j < sz; ++j) {
        Pt c = poly[i][(j + st) % sz];
        Pt d = poly[i][(j + st + 1) % sz];
        if (sign((a - b) ^ (c - d)) != 0) {
          int ok1 = ori(c, a, b) == 1;
          int ok2 = ori(d, a, b) == 1;
          if (ok1 ^ ok2) event.emplace_back(LinesInter({a, b}, {c, d}), ok1 ? 1 : -1);
        } else if (ori(c, a, b) == 0 && sign((a - b) * (c - d)) > 0 && i <= cid) {
          event.emplace_back(c, -1);
          event.emplace_back(d, 1);
        }
      }
    }
    sort(all(event), [&](pair <Pt, int> i, pair <Pt, int> j) {
      return ((a - i.first) * (a - b)) < ((a - j.first) * (a - b));
    });
    int now = 0;
    Pt lst = a;
    for (auto [x, y] : event) {
      if (btw(a, b, lst) && btw(a, b, x) && !now)
        ans += lst ^ x;
      now += y, lst = x;
    }
  };
  for (int i = 0; i < n; ++i) {
    int sz = poly[i].size();
    for (int j = 0; j < sz; ++j)
      solve(poly[i][j], poly[i][(j + 1) % sz], i);
  }
  return ans / 2;
}