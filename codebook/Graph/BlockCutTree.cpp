vector<vector<int>> g, _g;
vector<int> dep, low, stk;
void dfs(int i, int p) {
  dep[i] = low[i] = ~p ? dep[p] + 1 : 0;
  stk.push_back(i);
  for (int j : g[i]) if (j != p) {
    if (dep[j] == -1) {
      dfs(j, i), low[i] = min(low[i], low[j]);
      if (low[j] >= dep[i]) {
        int id = _g.size();
        _g.emplace_back();
        while (stk.back() != j) {
          int x = stk.back();
          stk.pop_back();
          _g[x].push_back(id), _g[id].push_back(x);
        }
        stk.pop_back();
        _g[j].push_back(id), _g[id].push_back(j);
        _g[i].push_back(id), _g[id].push_back(i);
      }
    } else low[i] = min(low[i], dep[j]);
  }
}