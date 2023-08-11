//a * p.first + b * p.second = gcd(a, b)
pair<ll, ll> extgcd(ll a, ll b) {
  pair<ll, ll> res, tmp;
  ll f = 1, g = 1;
  if (a < 0) a *= -1, f *= -1;
  if (b < 0) b *= -1, g *= -1;
  if (b == 0) return {f, 0};
  tmp = extgcd(b, a % b);
  res.first = tmp.second * f;
  res.second = (tmp.first - tmp.second * (a / b)) * g;
  return res;
}