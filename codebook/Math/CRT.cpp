pair<ll, ll> CRT(ll x1, ll m1, ll x2, ll m2) {
  ll g = gcd(m1, m2);
  if ((x2 - x1) % g) return make_pair(-1, -1);// no sol
  m1 /= g, m2 /= g;
  pair<ll, ll> p = extgcd(m1, m2);
  ll lcm = m1 * m2 * g;
  ll res = p.first * (x2 - x1) * m1 + x1;
  // be careful with overflow
  return make_pair((res % lcm + lcm) % lcm, lcm);
}