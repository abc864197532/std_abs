struct SAT {
  vector <int> g[N << 1], stk;
  int dep[N << 1], low[N << 1], scc_id[N << 1];
  int n, _id, _t;
  bool is[N];
  SAT() {}
  void init(int _n) {
    n = _n, _id = _t = 0;
    for (int i = 0; i < 2 * n; ++i)
      g[i].clear(), dep[i] = scc_id[i] = -1;
    stk.clear();
  }
  void add_edge(int x, int y) {g[x].push_back(y);}
  int rev(int i) {return i < n ? i + n : i - n;}
  void add_ifthen(int x, int y) {add_clause(rev(x), y);}
  void add_clause(int x, int y) {
    add_edge(rev(x), y);
    add_edge(rev(y), x);
  }
  void dfs(int i) {
    dep[i] = low[i] = _t++, stk.pb(i);
    for (int j : g[i]) if (scc_id[j] == -1) {
      if (dep[j] == -1) dfs(j);
      low[i] = min(low[i], low[j]);
    }
    if (low[i] == dep[i]) {
      int id = _id++, x;
      do {
        x = stk.back(), stk.pop_back();
        scc_id[x] = id;
      } while (x != i);
    }
  }
  bool solve() {
    // is[i] = true -> i, is[i] = false -> -i
    for (int i = 0; i < 2 * n; ++i) if (dep[i] == -1)
      dfs(i);
    for (int i = 0; i < n; ++i) {
      if (scc_id[i] == scc_id[i + n]) return false;
      if (scc_id[i] < scc_id[i + n]) is[i] = true;
      else is[i] = false;
    }
    return true;
  }
};