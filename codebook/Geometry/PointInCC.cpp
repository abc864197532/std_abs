// return q's relation with circumcircle of tri(p[0],p[1],p[2])
bool in_cc(array<Pt, 3> p, Pt q) {
  __int128 det = 0;
  for (int i = 0; i < 3; ++i) 
    det += __int128(abs2(p[i]) - abs2(q)) * ((p[(i + 1) % 3] - q) ^ (p[(i + 2) % 3] - q));
  return det > 0; // in: >0, on: =0, out: <0
}