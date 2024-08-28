template <typename T>
struct KM { // 0-based, remember to init
  const T INF = numeric_limits<T>::max() / 2;
  vector <vector <T>> w;
  vector <T> hl, hr, slk;
  vector <int> fl, fr, vl, vr, pre;
  queue <int> q; int n;
  bool check(int x) {
    if (vl[x] = 1, ~fl[x])
      return q.push(fl[x]), vr[fl[x]] = 1;
    while (~x) swap(x, fr[fl[x] = pre[x]]);
    return 0;
  }
  void bfs(int s) {
    fill(all(slk), INF), fill(all(vl), 0);
    fill(all(vr), 0);
    while (!q.empty()) q.pop();
    q.push(s), vr[s] = 1;
    while (true) {
      T d;
      while (!q.empty()) {
        int y = q.front(); q.pop();
        for (int x = 0; x < n; ++x) {
          d = hl[x] + hr[y] - w[x][y];
          if (!vl[x] && slk[x] >= d) {
            if (pre[x] = y, d) slk[x] = d;
            else if (!check(x)) return;
          }
        }
      }
      d = INF;
      for (int x = 0; x < n; ++x)
        if (!vl[x] && d > slk[x]) d = slk[x];
      for (int x = 0; x < n; ++x) {
        if (vl[x]) hl[x] += d;
        else slk[x] -= d;
        if (vr[x]) hr[x] -= d;
      }
      for (int x = 0; x < n; ++x)
        if (!vl[x] && !slk[x] && !check(x)) return;
    }
  }
  T solve() {
    fill(all(fl), -1), fill(all(fr), -1);
    fill(all(hr), 0);
    for (int i = 0; i < n; ++i)
      hl[i] = *max_element(all(w[i]));
    for (int i = 0; i < n; ++i) bfs(i);
    T res = 0;
    for (int i = 0; i < n; ++i) res += w[i][fl[i]];
    return res;
  }
  void init(int _n) {
    n = _n;
    w.assign(n, vector <T>(n, -INF));
    hl.resize(n), hr.resize(n), slk.resize(n);
    fl.resize(n), fr.resize(n), vl.resize(n);
    vr.resize(n), pre.resize(n);
  }
  void add_edge(int a, int b, T wei) { w[a][b] = wei; }
};