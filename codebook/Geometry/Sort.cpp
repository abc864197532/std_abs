// cmp in Basic: polar angle sort
// all points are on line ab. closer to a: front
bool cmp_line(Pt s, Pt t, Pt a, Pt b) {
  Pt v = a - b;
  if (sign(v.x)) return sign(s.x - t.x) == sign(v.x);
  else return sign(s.y - t.y) == sign(v.y);
}
// intersect points polar angle sort, deno: positive
bool cmp_fraction_polar(pair<Pt, ll> o, pair<Pt, ll> s, pair<Pt, ll> t) { // C^3 / C^2
  Pt u = s.first * o.second - o.first * s.second; //C^5
  Pt v = t.first * o.second - o.first * t.second; //C^5
  // u /= gcd(u.x, u.y) might lower the range to C
  return cmp(u, v);
}