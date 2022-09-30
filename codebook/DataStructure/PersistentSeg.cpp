struct Seg {
  // Persistent Segment Tree, single point modify, range query sum
  // 0-indexed, [l, r)
  static Seg mem[M], *pt;
  int l, r, m, val;
  Seg* ch[2];
  Seg () = default;
  Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1), val(0) {
    if (r - l > 1) {
      ch[0] = new (pt++) Seg(l, m);
      ch[1] = new (pt++) Seg(m, r);
    }
  }
  void pull() {val = ch[0]->val + ch[1]->val;}
  Seg* modify(int p, int v) {
    Seg *now = new (pt++) Seg(*this);
    if (r - l == 1) {
      now->val = v;
    } else {
      now->ch[p >= m] = ch[p >= m]->modify(p, v);
      now->pull();
    }
    return now;
  }
  int query(int a, int b) {
    if (a <= l && r <= b) return val;
    int ans = 0;
    if (a < m) ans += ch[0]->query(a, b);
    if (m < b) ans += ch[1]->query(a, b);
    return ans;
  }
} Seg::mem[M], *Seg::pt = mem;
// Init Tree
Seg *root = new (Seg::pt++) Seg(0, n);