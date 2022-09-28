//a * p.first + b * p.second = gcd(a, b)
pair<ll, ll> extgcd(ll a, ll b) {
  pair<ll, ll> res;
  if (a < 0) {
    res = extgcd(-a, b);
    res.first *= -1;
    return res;
  }
  if (b < 0) {
    res = extgcd(a, -b);
    res.second *= -1;
    return res;
  }
  if (b == 0) return {1, 0};
  res = extgcd(b, a % b);
  return {res.second, res.first - res.second * (a / b)};
}