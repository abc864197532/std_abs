void PolarAngleSort(vector <Pt> &pts) {
    auto pos = [&](Pt a) {return a.y == 0 ? a.x < 0 : a.y > 0;};
    sort(all(pts), [&](Pt a, Pt b) {return pos(a) == pos(b) ? (a ^ b) > 0 : pos(a) < pos(b);});
}