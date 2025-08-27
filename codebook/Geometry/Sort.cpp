// cmp in Basic: polar angle sort
// all points are on line ab. closer to a: front
bool cmp_line(Pt s, Pt t, Pt a, Pt b) {
  Pt v = a - b;
  if (sign(v.x)) return sign(s.x - t.x) == sign(v.x);
  else return sign(s.y - t.y) == sign(v.y);
} // 3dc688
// intersect points polar angle sort, deno: positive
bool cmp_fraction_polar(pair<Pt, ll> o, pair<Pt, ll> s, pair<Pt, ll> t) { // C^3 / C^2
  Pt u = s.first * o.second - o.first * s.second; //C^5
  Pt v = t.first * o.second - o.first * t.second; //C^5
  // u /= gcd(u.x, u.y) might lower the range to C
  return cmp(u, v);
} // 2d4450
struct Polar_Seg {
  Pt a, b; // ori(Pt(0, 0), a, b) > 0
  bool operator < (const Polar_Seg &o) const {
    if (btwangle(Pt(0, 0), a, b, o.a, 0)) {
      if (a == o.a) return ori(o.b, a, b) == -1;
      if (b == o.a) return false;
      return ori(o.a, a, b) == -1;
    }
    if (b == o.a) return false;
    return ori(a, o.a, o.b) == 1;
  }
};
struct Arc { // contain(a, b): circle a in circle b?
	Cir c; int s; // 0 -> up, 1 -> down
	bool operator < (const Arc &b) const {
		if (c.id == b.c.id) return s < b.s;
		if (contain(c, b.c)) return b.s == 1;
		else if (contain(b.c, c)) return s == 0;
		else if (c.o.y == b.c.o.y) return c.id < b.c.id;
	  else return c.o.y > b.c.o.y;
	}
};