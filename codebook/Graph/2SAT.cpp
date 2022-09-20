struct SAT {
    vector<vector<int>> g;
    vector<int> dep, low, scc_id;
    vector<bool> is;
    vector<int> stk;
    int n, _id;
    SAT() {}
    void init(int _n) {
        n = _n;
        _id = 0;
        g.assign(2 * n, vector<int>());
        dep.assign(2 * n, -1);
        low.assign(2 * n, -1);
        scc_id.assign(2 * n, -1);
        is.assign(2 * n, false);
        stk.clear();
    }
    void add_edge(int x, int y) {
        g[x].push_back(y);
    }
    int rev(int i) {
        return i < n ? i + n : i - n;
    }
    void add_clause(int x, int y) {
        add_edge(rev(x), y);
        add_edge(rev(y), x);
    }
    void add_ifthen(int x, int y) {
        add_clause(rev(x), y);
    }
    void dfs(int i, int p) {
        dep[i] = low[i] = ~p ? dep[p] + 1 : 0;
        stk.push_back(i);
        for (int j : g[i])
            if (j != p && scc_id[j] == -1) {
                if (dep[j] == -1)
                    dfs(j, i);
                low[i] = min(low[i], low[j]);
            }
        if (low[i] == dep[i]) {
            int id = _id++;
            while (stk.back() != i) {
                int x = stk.back();
                stk.pop_back();
                scc_id[x] = id;
            }
            stk.pop_back();
            scc_id[i] = id;
        }
    }
    bool solve() {
        for (int i = 0; i < 2 * n; ++i)
            if (dep[i] == -1)
                dfs(i, -1);
        for (int i = 0; i < n; ++i) {
            if (scc_id[i] == scc_id[i + n])
                return false;
            if (scc_id[i] < scc_id[i + n])
                is[i] = true;
            else
                is[i + n] = true;
        }
        return true;
    }
};
