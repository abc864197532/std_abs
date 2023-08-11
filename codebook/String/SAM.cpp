struct SAM {
  int ch[N][26], len[N], link[N], pos[N], cnt[N], sz;
  // node -> strings with the same endpos set
  // length in range [len(link) + 1, len]
  // node's endpos set -> pos in the subtree of node
  // link -> longest suffix with different endpos set
  // len  -> longest suffix
  // pos  -> end position
  // cnt  -> size of endpos set
  SAM () {len[0] = 0, link[0] = -1, pos[0] = 0, cnt[0] = 0, sz = 1;}
  void build(string s) {
    int last = 0;
    for (int i = 0; i < s.length(); ++i) {
      char c = s[i];
      int cur = sz++;
      len[cur] = len[last] + 1, pos[cur] = i + 1;
      int p = last;
      while (~p && !ch[p][c - 'a'])
        ch[p][c - 'a'] = cur, p = link[p];
      if (p == -1) link[cur] = 0;
      else {
        int q = ch[p][c - 'a'];
        if (len[p] + 1 == len[q]) {
          link[cur] = q;
        } else {
          int nxt = sz++;
          len[nxt] = len[p] + 1, link[nxt] = link[q];
          pos[nxt] = 0;
          for (int j = 0; j < 26; ++j)
            ch[nxt][j] = ch[q][j];
          while (~p && ch[p][c - 'a'] == q)
            ch[p][c - 'a'] = nxt, p = link[p];
          link[q] = link[cur] = nxt;
        }
      }
      cnt[cur]++;
      last = cur;
    }
    vector <int> p(sz);
    iota(all(p), 0);
    sort(all(p),
      [&](int i, int j) {return len[i] > len[j];});
    for (int i = 0; i < sz; ++i)
      cnt[link[p[i]]] += cnt[p[i]];
  }
} sam;