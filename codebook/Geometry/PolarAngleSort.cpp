void PolarAngleSort(vector <Pt> &pts) {
  auto pos = [&](Pt a) {return sign(a.y) == 0 ? sign(a.x) < 0 : sign(a.y) > 0;};
  sort(all(pts), [&](Pt a, Pt b) {return pos(a) == pos(b) ? sign(a ^ b) > 0 : pos(a) < pos(b);});
}