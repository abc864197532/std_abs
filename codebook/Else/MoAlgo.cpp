struct MoSolver {
  struct query {
    int l, r, id;
    bool operator < (const query &o) {
      if (l / C == o.l / C) return (l / C) & 1 ? r > o.r : r < o.r;
      return l / C < o.l / C;
    }
  };
  int cur_ans;
  vector <int> ans;
  void add(int x) {
    // do something
  }
  void sub(int x) {
    // do something
  }
  vector <query> Q;
  void add_query(int l, int r, int id) {
    // [l, r)
    Q.push_back({l, r, id});
    ans.push_back(0);
  }
  void run() {
    sort(Q.begin(), Q.end());
    int pl = 0, pr = 0;
    cur_ans = 0;
    for (query &i : Q) {
      while (pl > i.l)
        add(a[--pl]);
      while (pr < i.r)
        add(a[pr++]);
      while (pl < i.l)
        sub(a[pl++]);
      while (pr > i.r)
        sub(a[--pr]);
      ans[i.id] = cur;
    }
  }
};