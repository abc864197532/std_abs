struct ChthollyTree {
  struct interval {
    int l, r;
    ll v;
    interval (int _l, int _r, ll _v) : l(_l), r(_r), v(_v) {}
  };
  struct cmp {
    bool operator () (const interval &a, const interval& b) const {
      return a.l < b.l;
    }
  };
  set <interval, cmp> s;
  vector <interval> split(int l, int r) {
    // split into [0, l), [l, r), [r, n) and return [l, r)
    vector <interval> del, ans, re;
    auto it = s.lower_bound(interval(l, -1, 0));
    if (it != s.begin() && (it == s.end() || l < it->l)) {
      --it;
      del.pb(*it);
      if (r < it->r) {
        re.pb(interval(it->l, l, it->v));
        ans.pb(interval(l, r, it->v));
        re.pb(interval(r, it->r, it->v));
      } else {
        re.pb(interval(it->l, l, it->v));
        ans.pb(interval(l, it->r, it->v));
      }
      ++it;
    }
    for (; it != s.end() && it->r <= r; ++it) {
      ans.pb(*it);
      del.pb(*it);
    }
    if (it != s.end() && it->l < r) {
      del.pb(*it);
      ans.pb(interval(it->l, r, it->v));
      re.pb(interval(r, it->r, it->v));
    }
    for (interval &i : del)
      s.erase(i);
    for (interval &i : re)
      s.insert(i);
    return ans;
  }
  void merge(vector <interval> a) {
    for (interval &i : a)
      s.insert(i);
  }
};