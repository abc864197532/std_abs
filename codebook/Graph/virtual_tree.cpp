vector<vector<int>> _g;
vector<int> st, ed, stk;

void solve(vector<int> v) {
    sort(all(v), [&](int x, int y) {return st[x] < st[y];});
    int sz = v.size();
    for (int i = 0; i < sz - 1; ++i)
        v.push_back(lca(v[i], v[i + 1]));
    sort(all(v), [&](int x, int y) {return st[x] < st[y];});
    v.resize(unique(all(v)) - v.begin());
    stk.clear();
    stk.push_back(v[0]);
    for (int i = 1; i < v.size(); ++i) {
        int x = v[i];
        while (ed[stk.back()] < ed[x])
            stk.pop_back();
        _g[stk.back()].push_back(x);
        stk.push_back(x);
    }
    // do something
    for (int i : v)
        _g[i].clear();
}
