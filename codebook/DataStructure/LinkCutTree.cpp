// vertex-weighted, path add, path multiply, path query sum
struct LCT {
  int ch[N][2], pa[N], sz[N], _id;
  ll v[N], lz_mul[N], lz_add[N], sum[N];
  bool rev[N];
  LCT() : _id(1) {}
  int newnode() {
    int x = _id++;
    ch[x][0] = ch[x][1] = pa[x] = 0, sz[x] = 1;
    v[x] = lz_add[x] = sum[x] = 0, lz_mul[x] = 1;
    rev[x] = false;
    return x;
  }
  void pull(int i) {
    sum[i] = v[i], sz[i] = 1;
    if (ch[i][0]) sum[i] += sum[ch[i][0]], sz[i] += sz[ch[i][0]];
    if (ch[i][1]) sum[i] += sum[ch[i][1]], sz[i] += sz[ch[i][1]];
  }
  void push(int i) {
    if (lz_mul[i] != 1) mul(ch[i][0], lz_mul[i]), mul(ch[i][1], lz_mul[i]), lz_mul[i] = 1;
    if (lz_add[i]) add(ch[i][0], lz_add[i]), add(ch[i][1], lz_add[i]), lz_add[i] = 0;
    if (rev[i]) reverse(ch[i][0]), reverse(ch[i][1]), rev[i] = false;
  }
  void reverse(int i) {
    if (!i) return;
    swap(ch[i][0], ch[i][1]);
    rev[i] ^= true;
  }
  bool isrt(int i) {// rt of splay
    if (!pa[i]) return true;
    return ch[pa[i]][0] != i && ch[pa[i]][1] != i;
  }
  void rotate(int i) {
    int p = pa[i], x = ch[p][1] == i, c = ch[i][!x], gp = pa[p];
    if (ch[gp][0] == p) ch[gp][0] = i;
    else if (ch[gp][1] == p) ch[gp][1] = i;
    pa[i] = gp, ch[i][!x] = p, pa[p] = i;
    ch[p][x] = c, pa[c] = p;
    pull(p), pull(i);
  }
  void splay(int i) {
    vector<int> anc;
    anc.push_back(i);
    while (!isrt(anc.back())) anc.push_back(pa[anc.back()]);
    while (!anc.empty()) push(anc.back()), anc.pop_back();
    while (!isrt(i)) {
      int p = pa[i];
      if (!isrt(p)) rotate(ch[p][1] == i ^ ch[pa[p]][1] == p ? i : p);
      rotate(i);
    }
  }
  void access(int i) {
    int last = 0;
    while (i) {
      splay(i), ch[i][1] = last;
      pull(i), last = i, i = pa[i];
    }
  }
  void makert(int i) {
    access(i), splay(i), reverse(i);
  }
  void link(int i, int j) {
    // assert(findrt(i) != findrt(j));
    makert(i), pa[i] = j;
  }
  void cut(int i, int j) {
    makert(i), access(j), splay(i);
    // assert(sz[i] == 2 && ch[i][1] == j);
    ch[i][1] = pa[j] = 0, pull(i);
  }
  int findrt(int i) {
    access(i), splay(i);
    while (ch[i][0]) push(i), i = ch[i][0];
    splay(i);
    return i;
  }
  // custom functions
  void mul(int i, ll d) {
    if (!i)
      return;
    v[i] *= d, lz_mul[i] *= d;
    lz_add[i] *= d, sum[i] *= d;
  }
  void add(int i, ll d) {
    if (!i) return;
    v[i] += d, lz_add[i] += d, sum[i] += d * sz[i];
  }
  void mul_path(int i, int j, ll d) {
    // assert(findrt(i) == findrt(j));
    makert(i), access(j);
    splay(i), mul(i, d);
  }
  void add_path(int i, int j, ll d) {
    // assert(findrt(i) == findrt(j));
    makert(i), access(j), splay(i), add(i, d);
  }
  ll query_path(int i, int j) {
    // assert(findrt(i) == findrt(j));
    makert(i), access(j), splay(i);
    return sum[i];
  }
};