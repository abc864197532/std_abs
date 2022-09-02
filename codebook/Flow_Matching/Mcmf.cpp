struct MCMF {
    const int INF = 1 << 30;
    struct Edge {
        int v, id, revid, f, c;
        Edge (int _v, int _f, int _c, int _id, int _revid) : v(_v), f(_f), c(_c), id(_id), revid(_revid) {}
    };
    vector <vector <Edge>> adj;
    vector <pair <int, int>> rt;
    vector <int> dis;
    int n, s, t;
    MCMF () = default;
    MCMF (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        adj.resize(n);
    }
    void add_edge(int u, int v, int f, int c) {
        adj[u].push_back(Edge(v, f, c, adj[u].size(), adj[v].size()));
        adj[v].push_back(Edge(u, 0, -c, adj[v].size(), adj[u].size() - 1));
    }
    bool SPFA() {
        rt.assign(n, make_pair(-1, -1));
        dis.assign(n, INF);
        vector <bool> vis(n, false);
        queue <int> q;
        q.push(s), dis[s] = 0, vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = false;
            for (Edge &e : adj[v]) if (e.f > 0 && dis[e.v] > dis[v] + e.c) {
                dis[e.v] = dis[v] + e.c, rt[e.v] = make_pair(v, e.id);
                if (!vis[e.v]) vis[e.v] = true, q.push(e.v);
            }
        }
        return dis[t] != INF;
    }
    pair <int, int> runFlow() { // cost, flow
        int cost = 0, flow = 0;
        while (SPFA()) {
            vector <pair <int, int>> E;
            int v = t, addflow = INF;
            while (v != s) {
                addflow = min(addflow, adj[rt[v].first][rt[v].second].f);
                E.push_back(rt[v]), v = rt[v].first;
            }
            for (pair <int, int> a : E) {
                adj[a.first][a.second].f -= addflow;
                adj[adj[a.first][a.second].v][adj[a.first][a.second].revid].f += addflow;
            }
            flow += addflow, cost += addflow * dis[t];
        }
        return make_pair(cost, flow);
    }
};