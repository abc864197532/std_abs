struct SAT { // 0-based, need SCC
  int n; SCC scc; vector <int> is;
  int rev(int x) { return x < n ? x + n : x - n; }
  void add_ifthen(int x, int y) {
    add_clause(rev(x), y); }
  void add_clause(int x, int y) {
    scc.add_edge(rev(x), y);
    scc.add_edge(rev(y), x); }
  bool solve() {
    // is[i] = true -> i, is[i] = false -> -i
    scc.build();
    for (int i = 0; i < n; ++i) {
      if (scc.scc_id[i] == scc.scc_id[i + n])
        return false;
      is[i] = scc.scc_id[i] < scc.scc_id[i + n];
    }
    return true;
  }
  SAT (int _n) : n(_n), scc(2 * n), is(n) {}
};