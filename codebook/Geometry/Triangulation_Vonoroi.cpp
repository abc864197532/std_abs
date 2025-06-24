// all coord. is even, half plane intersection
vector<vector<Line>> build_voronoi_line(vector<Pt> arr) {
  int n = sz(arr);
  Delaunay tool(arr);
  vector<vector<Line>> vec(n);
  for (int i = 0; i < n; ++i)
    for (auto e : tool.head[i]) {
      int u = tool.oidx[i], v = tool.oidx[e.id];
      Pt m = (arr[v] + arr[u]) / 2, d = perp(arr[v] - arr[u]);
      vec[u].pb(Line{m, m + d});
    }
  return vec;
}