template <typename T>
struct KM { // 0-base
    T w[N][N], hl[N], hr[N], slk[N];
    int fl[N], fr[N], pre[N], n;
    bool vl[N], vr[N];
    const T INF = 1e9;
    queue <int> q; 
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) w[i][j] = -INF;
    }
    void add_edge(int a, int b, int wei) {
        w[a][b] = wei;
    }
    bool Check(int x) {
        if (vl[x] = 1, ~fl[x]) return q.push(fl[x]), vr[fl[x]] = 1;
        while (~x) swap(x, fr[fl[x] = pre[x]]);
        return 0;
    }
    void Bfs(int s) {
        fill(slk, slk + n, INF), fill(vl, vl + n, 0), fill(vr, vr + n, 0);
        q.push(s), vr[s] = 1;
        while (1) {
            T d;
            while (!q.empty()) {
                int y = q.front(); q.pop();
                for (int x = 0; x < n; ++x)
                    if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - w[x][y]))
                        if (pre[x] = y, d) slk[x] = d;
                        else if (!Check(x)) return;
            }
            d = INF;
            for (int x = 0; x < n; ++x)
                if (!vl[x] && d > slk[x]) d = slk[x];
            for (int x = 0; x < n; ++x) {
                if (vl[x]) hl[x] += d;
                else slk[x] -= d;
                if (vr[x]) hr[x] -= d;
            }
            for (int x = 0; x < n; ++x) if (!vl[x] && !slk[x] && !Check(x)) return;
        }
    }
    T Solve() {
        fill(fl, fl + n, -1), fill(fr, fr + n, -1), fill(hr, hr + n, 0);
        for (int i = 0; i < n; ++i) hl[i] = *max_element(w[i], w[i] + n);
        for (int i = 0; i < n; ++i) Bfs(i);
        T res = 0;
        for (int i = 0; i < n; ++i) res += w[i][fl[i]];
        return res;
    }
};