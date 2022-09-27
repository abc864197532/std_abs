void fwt(vector <int> &a) {
  // and : a[j] += x;
  //     : a[j] -= x;
  // or  : a[j ^ (1 << i)] += y;
  //     : a[j ^ (1 << i)] -= y;
  // xor : a[j] = x - y, a[j ^ (1 << i)] = x + y;
  //     : a[j] = (x - y) / 2, a[j ^ (1 << i)] = (x + y) / 2;
  int n = __lg(a.size());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 1 << n; ++j) if (j >> i & 1) {
      int x = a[j ^ (1 << i)], y = a[j];
      // do something
    }
  }
}