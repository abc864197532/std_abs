void all_lcs(string s, string t) { // 0-base
  vector<int> h(sz(t));
  iota(all(h), 0);
  for (int a = 0; a < sz(s); ++a) {
    int v = -1;
    for (int c = 0; c < sz(t); ++c)
      if (s[a] == t[c] || h[c] < v)
        swap(h[c], v);
    // LCS(s[0, a], t[b, c]) = 
    // c - b + 1 - sum([h[i] >= b] | i <= c)
    // h[i] might become -1 !!
  }
}