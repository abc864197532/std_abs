int to_left[N], to_right[N];
vector <array <int, 3>> rep; // l, r, len.
// substr( [l, r], len * 2) are tandem
void findRep(string &s, int l, int r) {
  if (r - l == 1) return;
  int m = l + r >> 1;
  findRep(s, l, m), findRep(s, m, r);
  string sl = s.substr(l, m - l);
  string sr = s.substr(m, r - m);
  vector <int> Z = buildZ(sr + "#" + sl);
  for (int i = l; i < m; ++i)
    to_right[i] = Z[r - m + 1 + i - l];
  reverse(all(sl));
  Z = buildZ(sl);
  for (int i = l; i < m; ++i)
    to_left[i] = Z[m - i - 1];
  reverse(all(sl));
  for (int i = l; i + 1 < m; ++i) {
    int k1 = to_left[i], k2 = to_right[i + 1];
    int len = m - i - 1;
    if (k1 < 1 || k2 < 1 || len < 2) continue;
    int tl = max(1, len - k2), tr = min(len - 1, k1);
    if (tl <= tr) rep.pb({i + 1 - tr, i + 1 - tl,len});
  }
  Z = buildZ(sr);
  for (int i = m; i < r; ++i) to_right[i] = Z[i - m];
  reverse(all(sl)), reverse(all(sr));
  Z = buildZ(sl + "#" + sr);
  for (int i = m; i < r; ++i)
    to_left[i] = Z[m - l + 1 + r - i - 1];
  reverse(all(sl)), reverse(all(sr));
  for (int i = m; i + 1 < r; ++i) {
    int k1 = to_left[i], k2 = to_right[i + 1];
    int len = i - m + 1;
    if (k1 < 1 || k2 < 1 || len < 2) continue;
    int tl = max(len - k2, 1), tr = min(len - 1, k1);
    if (tl <= tr)
      rep.pb({i + 1 - len - tr, i + 1 - len - tl,len});
  }
  Z = buildZ(sr + "#" + sl);
  for (int i = l; i < m; ++i)
    if (Z[r - m + 1 + i - l] >= m - i)
      rep.pb({i, i, m - i});
}