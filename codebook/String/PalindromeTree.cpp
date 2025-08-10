struct PAM {
  int ch[N][C], cnt[N], fail[N], len[N], _id;
  // 0 -> even root, 1 -> odd root
  PAM () { reset(); }
  int newnode() {
    fill_n(ch[_id], C, 0);
    cnt[_id] = fail[_id] = len[_id] = 0;
    return _id++;
  }
  void build(string s) {
    int lst = 1;
    for (int i = 0; i < sz(s); ++i) {
      while (s[i - len[lst] - 1] != s[i])
        lst = fail[lst];
      if (!ch[lst][s[i] - 'a'])  {
        int idx = newnode();
        len[idx] = len[lst] + 2;
        int now = fail[lst];
        while (s[i - len[now] - 1] != s[i])
          now = fail[now];
        fail[idx] = ch[now][s[i] - 'a'];
        ch[lst][s[i] - 'a'] = idx;
      }
      lst = ch[lst][s[i] - 'a'], cnt[lst]++;
    }
  }
  void build_count() {
    for (int i = _id - 1; i > 1; --i)
      cnt[fail[i]] += cnt[i];
  }
  void reset() { _id = 0, newnode(), newnode(), 
    len[0] = 0, fail[0] = 1, len[1] = -1; }
} pam;