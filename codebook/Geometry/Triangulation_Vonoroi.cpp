vector<Line> ls[N];
Line make_line(Pt p, Line l) {
  Pt d = l.b - l.a; d = perp(d);
  Pt m = (l.a + l.b) / 2; // remember to *2
  l = {m, m + d};
  if (ori(l.a, l.b, p) < 0) swap(l.a, l.b);
  return l;
}
void solve(vector <Pt> &oarr) {
  int n = oarr.size();
  map<pair <ll, ll>, int> mp;
  vector <Pt> arr = oarr;
  for (int i = 0; i < n; ++i)
    mp[{arr[i].x, arr[i].y}] = i;
  build(arr); // Triangulation
  for (auto *t : triang) {
    vector<int> p;
    for (int i = 0; i < 3; ++i) {
      pair <ll, ll> tmp = {t->p[i].x, t->p[i].y};
      if (mp.count(tmp)) p.pb(mp[tmp]);
    }
    for (int i = 0; i < sz(p); ++i)
      for (int j = i + 1; j < sz(p); ++j) { 
        Line l = {oarr[p[i]], oarr[p[j]]};
        ls[p[i]].pb(make_line(oarr[p[i]], l));
        ls[p[j]].pb(make_line(oarr[p[j]], l));
      }
  }
  for (int i = 0; i < n; ++i) 
    ls[i] = HalfPlaneInter(ls[i]);
}