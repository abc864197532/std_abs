vector<Line> tangent(Cir a, Cir b) {
#define Pij \
  Pt i = unit(b.o - a.o) * a.r, j = Pt(i.y, -i.x);\
  z.push_back({a.o + i, a.o + i + j});
#define deo(I,J) \
  double d = abs(a.o - b.o), e = a.r I b.r, o = acos(e / d);\
  Pt i = unit(b.o - a.o), j = rot(i, o), k = rot(i, -o);\
  z.push_back({a.o + j * a.r, b.o J j * b.r});\
  z.push_back({a.o + k * a.r, b.o J k * b.r});
  if (a.r < b.r) swap(a, b);
  vector<Line> z;
  if (abs(a.o - b.o) + b.r < a.r) return z;
  else if (sign(abs(a.o - b.o) + b.r - a.r) == 0) { Pij; } 
  else {
    deo(-,+); // inter
    // outer
    if (sign(d - a.r - b.r) == 0) { Pij; } 
    else if (d > a.r + b.r) { deo(+,-); }
  }
  return z;
}