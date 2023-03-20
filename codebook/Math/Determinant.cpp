ll Det(vector <vector <ll>> a) {
  int n = a.size();
  ll det = 1;
  for (int i = 0; i < n; ++i) {
    if (!a[i][i]) {
      det = -det;
      if (det < 0) det += mod;
      for (int j = i + 1; j < n; ++j) if (a[j][i]) {
        swap(a[j], a[i]);
        break;
      }
      if (!a[i][i]) return 0;
    }
    det = det * a[i][i] % mod;
    ll mul = mpow(a[i][i], mod - 2);
    for (int j = 0; j < n; ++j) a[i][j] = a[i][j] * mul % mod;
    for (int j = 0; j < n; ++j) if (i ^ j) {
      ll mul = a[j][i];
      for (int k = 0; k < n; ++k) {
        a[j][k] -= a[i][k] * mul % mod;
        if (a[j][k] < 0) a[j][k] += mod;
      }
    }
  }
  return det;
}