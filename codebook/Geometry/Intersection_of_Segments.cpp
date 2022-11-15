Pt LinesInter(Line a, Line b) {
  double abc = (a.b - a.a) ^ (b.a - a.a);
  double abd = (a.b - a.a) ^ (b.b - a.a);
  if (sign(abc - abd) == 0) return b.b;// no inter
  return (b.b * abc - b.a * abd) / (abc - abd);
}

vector<Pt> SegsInter(Line a, Line b) {
  if (btw(a.a, a.b, b.a)) return {b.a};
  if (btw(a.a, a.b, b.b)) return {b.b};
  if (btw(b.a, b.b, a.a)) return {a.a};
  if (btw(b.a, b.b, a.b)) return {a.b};
  if (ori(a.a, a.b, b.a) * ori(a.a, a.b, b.b) == -1 &&
      ori(b.a, b.b, a.a) * ori(b.a, b.b, a.b) == -1)
    return {LinesInter(a, b)};
  return {};
}