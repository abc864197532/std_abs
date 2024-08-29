struct SAT { // 0-based, need SCC
  int n; vector <pii> edge; vector <int> is;
  int rev(int x) { return x < n ? x + n : x - n; }
  void add_ifthen(int x, int y) {
    add_clause(rev(x), y); }
  void add_clause(int x, int y) {
    edge.emplace_back(rev(x), y);
    edge.emplace_back(rev(y), x); }
  bool solve() {
    // is[i] = true -> i, is[i] = false -> -i
    SCC scc(2 * n);
    for (auto [u, v] : edge) scc.add_edge(u, v);
    scc.build();
    for (int i = 0; i < n; ++i) {
      if (scc.scc_id[i] == scc.scc_id[i + n])
        return false;
      is[i] = scc.scc_id[i] < scc.scc_id[i + n];
    }
    return true;
  }
  SAT (int _n) : n(_n), is(n) {}
};