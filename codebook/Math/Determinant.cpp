int Det(vector <vector <int>> a) {
  int n = (int)a.size(), det = 1;
  for (int i = 0; i < n; ++i) {
    if (!a[i][i]) {
      det = sub(0, det);
      for (int j = i + 1; j < n; ++j) if (a[j][i]) {
        swap(a[j], a[i]);
        break;
      }
      if (!a[i][i]) return 0;
    }
    det = mul(det, a[i][i]);
    int tmp = Pow(a[i][i], mod - 2);
    for (int j = 0; j < n; ++j)
      a[i][j] = mul(a[i][j], tmp);
    for (int j = 0; j < n; ++j) if (i ^ j) {
      tmp = a[j][i];
      for (int k = 0; k < n; ++k) {
        a[j][k] = sub(a[j][k], mul(a[i][k], tmp));
      }
    }
  }
  return det;
}