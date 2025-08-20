struct SAM {
  int ch[2 * N][C], len[2 * N], link[2 * N], pos[2 * N], cnt[2 * N], _id;
  // node -> strings with the same endpos set
  // length in range [len(link) + 1, len]
  // node's endpos set -> pos in the subtree of node
  // link -> longest suffix with different endpos set
  // len  -> longest suffix
  // pos  -> end position
  // cnt  -> size of endpos set
  SAM () { reset(); }
  int newnode() {
    fill_n(ch[_id], C, 0);
    len[_id] = link[_id] = pos[_id] = cnt[_id] = 0;
    return _id++;
  }
  void build(string s) {
    int lst = 0;
    for (int i = 0; i < s.length(); ++i) {
      char c = s[i];
      int cur = newnode();
      len[cur] = len[lst] + 1, pos[cur] = i + 1;
      int p = lst;
      while (~p && !ch[p][c - 'a'])
        ch[p][c - 'a'] = cur, p = link[p];
      if (p == -1) link[cur] = 0;
      else {
        int q = ch[p][c - 'a'];
        if (len[p] + 1 == len[q]) {
          link[cur] = q;
        } else {
          int nxt = newnode();
          len[nxt] = len[p] + 1, link[nxt] = link[q];
          pos[nxt] = 0;
          for (int j = 0; j < C; ++j)
            ch[nxt][j] = ch[q][j];
          while (~p && ch[p][c - 'a'] == q)
            ch[p][c - 'a'] = nxt, p = link[p];
          link[q] = link[cur] = nxt;
        }
      }
      cnt[cur]++, lst = cur;
    }
  }
  // void build_count() {
  //   vector <int> p(_id);
  //   iota(all(p), 0);
  //   sort(all(p),
  //     [&](int i, int j) {return len[i] > len[j];});
  //   for (int i = 0; i < _id; ++i) if (~link[p[i]])
  //     cnt[link[p[i]]] += cnt[p[i]];
  // }
  void reset() { _id = 0, newnode(), link[0] = -1; }
} sam;