void RotatingSweepLine(vector <Pt> &pt) {
    int n = pt.size();
    vector <int> id(n), pos(n);
    vector <pair <int, int>> line;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i ^ j) line.emplace_back(i, j);
    sort(line.begin(), line.end(), [&](pair <int, int> i, pair <int, int> j) {
        Pt a = pt[i.second] - pt[i.first], b = pt[j.second] - pt[j.first];
        return (a.pos() == b.pos() ? (a ^ b) > 0 : a.pos() < b.pos());
    });
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j) {
        return (pt[i].y == pt[j].y ? pt[i].x < pt[j].x : pt[i].y < pt[j].y);
    });
    for (int i = 0; i < n; ++i)
        pos[id[i]] = i;
    for (auto [i, j] : line) {
        // point sort by the distance to line(i, j)
        // do something.
        tie(pos[i], pos[j], id[pos[i]], id[pos[j]]) = make_tuple(pos[j], pos[i], j, i);
    }
}