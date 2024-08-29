int dep[N], pa[N], to[N]; // pa[rt] = rt, to[rt] = rt
int lift(int x, int k) {
  k = dep[x] - k;
  while (dep[x] > k)
    x = dep[to[x]] < k ? pa[x] : to[x];
  return x;
}
void add(int p, int v) {
  dep[v] = dep[p] + 1, pa[v] = p;
  to[v] = dep[p] - dep[to[p]] ==
          dep[to[p]] - dep[to[to[p]]] ? to[to[p]] : p;
}