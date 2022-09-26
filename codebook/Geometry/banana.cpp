bool banana(Pt a, Pt b, Pt c, Pt d) { // segment ab and cd
  if (btw(a, b, c) || btw(a, b, d) || btw(c, d, a) || btw(c, d, b)) return true;
  return ori(a, b, c) * ori(a, b, d) == -1 && ori(c, d, a) * ori(c, d, b) == -1;
}
Pt intersect(Pt a, Pt b, Pt c, Pt d) { // segment ab and cd
  double abc = (b - a) ^ (c - a);
  double abd = (b - a) ^ (d - a);
  if (sign(abc - abd) == 0) return d;
  return (d * abc - c * abd) / (abc - abd);
}