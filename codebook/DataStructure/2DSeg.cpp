// 2D range add, range sum in log^2
struct seg {
  int l, r;
  ll sum, lz;
  seg *ch[2]{};
  seg(int _l, int _r) : l(_l), r(_r), sum(0), lz(0) {}
  void push() {
    if (lz) ch[0]->add(l, r, lz), ch[1]->add(l, r, lz), lz = 0;
  }
  void pull() { sum = ch[0]->sum + ch[1]->sum; }
  void add(int _l, int _r, ll d) {
    if (_l <= l && r <= _r) {
      sum += d * (r - l), lz += d;
      return;
    }
    if (!ch[0]) ch[0] = new seg(l, l + r >> 1), ch[1] = new seg(l + r >> 1, r);
    push();
    if (_l < l + r >> 1) ch[0]->add(_l, _r, d);
    if (l + r >> 1 < _r) ch[1]->add(_l, _r, d);
    pull();
  }
  ll qsum(int _l, int _r) {
    if (_l <= l && r <= _r) return sum;
    if (!ch[0]) return lz * (min(r, _r) - max(l, _l));
    push();
    ll res = 0;
    if (_l < l + r >> 1) res += ch[0]->qsum(_l, _r);
    if (l + r >> 1 < _r) res += ch[1]->qsum(_l, _r);
    return res;
  }
};
struct seg2 {
  int l, r;
  seg v, lz;
  seg2 *ch[2]{};
  seg2(int _l, int _r) : l(_l), r(_r), v(0, N), lz(0, N) {
    if (l < r - 1) ch[0] = new seg2(l, l + r >> 1), ch[1] = new seg2(l + r >> 1, r);
  }
  void add(int _l, int _r, int _l2, int _r2, ll d) {
    v.add(_l2, _r2, d * (min(r, _r) - max(l, _l)));
    if (_l <= l && r <= _r)
      return lz.add(_l2, _r2, d), void(0);
    if (_l < l + r >> 1)
        ch[0]->add(_l, _r, _l2, _r2, d);
    if (l + r >> 1 < _r)
        ch[1]->add(_l, _r, _l2, _r2, d);
  }
  ll qsum(int _l, int _r, int _l2, int _r2) {
    if (_l <= l && r <= _r) return v.qsum(_l2, _r2);
    ll d = min(r, _r) - max(l, _l);
    ll res = lz.qsum(_l2, _r2) * d;
    if (_l < l + r >> 1)
        res += ch[0]->qsum(_l, _r, _l2, _r2);
    if (l + r >> 1 < _r)
        res += ch[1]->qsum(_l, _r, _l2, _r2);
    return res;
  }
};