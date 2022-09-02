struct Dinic {
    const int INF = 1 << 30;
    struct Edge {
        int v, id, f;
        Edge (int _v, int _f, int _id) : v(_v), id(_id), f(_f) {}
    };
    vector <vector <Edge>> adj;
    vector <int> level;
    int n, s, t;
    Dinic () = default;
    Dinic (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {adj.resize(n);}
    void add_edge(int u, int v, int f) {
        adj[u].push_back(Edge(v, f, adj[v].size()));
        adj[v].push_back(Edge(u, 0, adj[u].size() - 1));
    }
    bool bfs() {
        level.assign(n, -1);
        queue <int> q;
        q.push(s), level[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (Edge e : adj[v]) {
                if (e.f > 0 && level[e.v] == -1) {
                    level[e.v] = level[v] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] != -1;
    }
    int dfs(int v, int minf) {
        if (v == t) 
            return minf;
        int ans = 0;
        for (Edge &e : adj[v]) {
            if (e.f > 0 && level[e.v] == level[v] + 1) {
                int nxtf = dfs(e.v, min(minf, e.f));
                ans += nxtf, minf -= nxtf, e.f -= nxtf, adj[e.v][e.id].f += nxtf;
                if (minf == 0) return ans;
            }
        }
        if (!ans) level[v] = -1;
        return ans;
    }
    int runFlow() {
        int ans = 0;
        while (bfs()) ans += dfs(s, INF);
        return ans;
    }
    vector <bool> vis;
    void runBfs() {
        vis.assign(n, false);
        queue <int> q;
        q.push(s), vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (Edge &e : adj[v]) if (e.f > 0 && !vis[e.v]) {
                q.push(e.v), vis[e.v] = true;
            }
        }
    }
};