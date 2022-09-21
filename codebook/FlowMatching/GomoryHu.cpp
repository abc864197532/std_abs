vector <array <int, 3>> GomoryHu(vector <vector <pii>> adj, int n) {
    // Tree edge min -> mincut (0-based)
    Dinic flow(n);
    for (int i = 0; i < n; ++i) for (auto [j, w] : adj[i])
        flow.add_edge(i, j, w);
    flow.record();
    vector <array <int, 3>> ans;
    vector <int> rt(n);
    for (int i = 0; i < n; ++i) rt[i] = 0;
    for (int i = 1; i < n; ++i) {
        int t = rt[i];
        flow.reset(); // clear flows on all edge
        ans.push_back({i, t, flow.solve(i, t)});
        flow.runbfs(i);
        for (int j = i + 1; j < n; ++j) if (rt[j] == t && flow.vis[j]) {
            rt[j] = i;
        }
    }
    return ans;
}