void RotatingCaliper(vector <Pt> &pts) {
    int n = pts.size();
    for (int i = 0, j = 2; i < n; ++i) {
        int ni = (i + 1) % n;
        while (true) {
            int nj = (j + 1) % n;
            if (area(pts[j], pts[i], pts[ni]) < area(pts[nj], pts[i], pts[ni])) {
                j = nj;
            } else {
                break;
            }
        }
        // do something
    }
}