/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle. */
struct Edge {
  int id; // oidx[id]
  list<Edge>::iterator twin;
  Edge (int _id = 0) : id(_id) {}
};
struct Delaunay { // 0-base
  int n;
  vector<int> oidx;
  vector<list<Edge>> head; // result udir. graph
  vector<Pt> p;
  Delaunay (vector<Pt> _p) : n(sz(_p)), oidx(n), head(n), p(_p) {
    iota(all(oidx), 0);
    sort(all(oidx), [&](int a, int b) {
      return make_pair(_p[a].x, _p[a].y) < make_pair(_p[b].x, _p[b].y); });
    for (int i = 0; i < n; ++i) p[i] = _p[oidx[i]];
    divide(0, n - 1);
  }
  void add_edge(int u, int v) {
    head[u].push_front(Edge(v));
    head[v].push_front(Edge(u));
    head[u].begin()->twin = head[v].begin();
    head[v].begin()->twin = head[u].begin();
  }
  void divide(int l, int r) {
    if (l == r) return;
    if (l + 1 == r) return add_edge(l, l + 1);
    int mid = (l + r) >> 1, nw[2] = {l, r};
    divide(l, mid), divide(mid + 1, r);
    auto gao = [&](int t) {
      Pt pts[2] = {p[nw[0]], p[nw[1]]};
      for (auto it : head[nw[t]]) {
        int v = ori(pts[1], pts[0], p[it.id]);
        if (v > 0 || (v == 0 && abs2(pts[t ^ 1] - p[it.id]) < abs2(pts[1] - pts[0])))
          return nw[t] = it.id, true;
      }
      return false;
    };
    while (gao(0) || gao(1));
    add_edge(nw[0], nw[1]); // add tangent
    while (true) {
      Pt pts[2] = {p[nw[0]], p[nw[1]]};
      int ch = -1, sd = 0;
      for (int t = 0; t < 2; ++t)
        for (auto it : head[nw[t]])
          if (ori(pts[0], pts[1], p[it.id]) > 0 && (ch == -1 || point_in_cc({pts[0], pts[1], p[ch]}, p[it.id])))
            ch = it.id, sd = t;
      if (ch == -1) break; // upper common tangent
      for (auto it = head[nw[sd]].begin(); it != head[nw[sd]].end(); )
        if (lines_intersect_check({pts[sd], p[it->id]}, 0, {pts[sd ^ 1], p[ch]}, 0, 1))
          head[it->id].erase(it->twin), head[nw[sd]].erase(it++);
        else ++it;
      nw[sd] = ch, add_edge(nw[0], nw[1]);
    }
  }
};