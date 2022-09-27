vector <Pt> Minkowski(vector <Pt> a, vector <Pt> b) {
  a = ConvexHull(a), b = ConvexHull(b);
  int n = a.size(), m = b.size();
  vector <Pt> c = {a[0] + b[0]}, s1, s2; 
  for(int i = 0; i < n; ++i) 
    s1.pb(a[(i + 1) % n] - a[i]);
  for(int i = 0; i < m; i++) 
    s2.pb(b[(i + 1) % m] - b[i]);
  for(int p1 = 0, p2 = 0; p1 < n || p2 < m;)
    if (p2 == m || (p1 < n && sign(s1[p1] ^ s2[p2]) >= 0))
      c.pb(c.back() + s1[p1++]);
    else
      c.pb(c.back() + s2[p2++]);
  return ConvexHull(c);
}