vector <Pt> ConvexHull(vector <Pt> pt) {
  int n = pt.size();
  sort(all(pt), [&](Pt a, Pt b)
    {return a.x == b.x ? a.y < b.y : a.x < b.x;});
  vector <Pt> ans = {pt[0]};
  for (int t : {0, 1}) {
    int m = ans.size();
    for (int i = 1; i < n; ++i) {
      while (ans.size() > m && ori(ans[ans.size() - 2],
        ans.back(), pt[i]) <= 0) ans.pop_back();
      ans.pb(pt[i]);
    }
    reverse(all(pt));
  }
  if (ans.size() > 1) ans.pop_back();
  return ans;
}