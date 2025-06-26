auto minkowski(vector<Pt> a, vector<Pt> b) {
  a = convex_hull(a), b = convex_hull(b);
  int n = sz(a), m = sz(b);
  vector<Pt> c = {a[0] + b[0]}, s1, s2; 
  for(int i = 0; i < n; ++i) 
    s1.pb(a[(i + 1) % n] - a[i]);
  for(int i = 0; i < m; i++) 
    s2.pb(b[(i + 1) % m] - b[i]);
  for(int p1 = 0, p2 = 0; p1 < n || p2 < m;)
    if (p2 == m || (p1 < n && sign(s1[p1] ^ s2[p2]) >= 0))
      c.pb(c.back() + s1[p1++]);
    else
      c.pb(c.back() + s2[p2++]);
  return convex_hull(c);
}