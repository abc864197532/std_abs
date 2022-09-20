vector<int> low, dep, bcc_id, stk;
vector<bool> vis;
int _id;

void dfs(int i, int p) {
    low[i] = dep[i] = ~p ? dep[p] + 1 : 0;
    stk.push_back(i);
    vis[i] = true;
    for (int j : g[i])
        if (j != p) {
            if (!vis[j])
                dfs(j, i), low[i] = min(low[i], low[j]);
            else
                low[i] = min(low[i], dep[j]);
        }
    if (low[i] == dep[i]) {
        int id = _id++;
        while (stk.back() != i) {
            int x = stk.back();
            stk.pop_back();
            bcc_id[x] = id;
        }
        stk.pop_back();
        bcc_id[i] = id;
    }
}
