// return p4 is strictly in circumcircle of tri(p1,p2,p3)
ll sqr(ll x) { return x * x; }
bool in_cc(const Pt &p1, const Pt &p2, const Pt &p3, const Pt &p4) {
  ll u11 = p1.x - p4.x; ll u12 = p1.y - p4.y;
  ll u21 = p2.x - p4.x; ll u22 = p2.y - p4.y;
  ll u31 = p3.x - p4.x; ll u32 = p3.y - p4.y;
  ll u13 = sqr(p1.x) - sqr(p4.x) + sqr(p1.y) - sqr(p4.y);
  ll u23 = sqr(p2.x) - sqr(p4.x) + sqr(p2.y) - sqr(p4.y);
  ll u33 = sqr(p3.x) - sqr(p4.x) + sqr(p3.y) - sqr(p4.y);
  __int128 det = (__int128)-u13 * u22 * u31 + (__int128)u12 * u23 * u31 + (__int128)u13 * u21 * u32 - (__int128)u11 * u23 * u32 - (__int128)u12 * u21 * u33 + (__int128)u11 * u22 * u33;
  return det > 0;
}