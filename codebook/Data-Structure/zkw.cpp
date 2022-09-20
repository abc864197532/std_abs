int N = 1 << 18; // N >= maxn + 2
ll mx[N << 1], sum[N << 1], lz[N << 1];

void add(int l, int r, ll d) { // [l, r), 0-based
    int len = 1, cntl = 0, cntr = 0;
    for (l += N, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        sum[l] += cntl * d, sum[r] += cnt[r] * d;
        if (len > 1) {
            mx[l] = max(mx[l << 1], mx[l << 1 | 1]) + lz[l];
            mx[r] = max(mx[r << 1], mx[r << 1 | 1]) + lz[r];
        }
        if (~l & 1)
            sum[l ^ 1] += d * len, mx[l ^ 1] += d, lz[l ^ 1] += d, cntl += len;
        if (r & 1)
            sum[r ^ 1] += d * len, mx[r ^ 1] += d, lz[r ^ 1] += d, cntr += len;
    }
    sum[l] += cntl * d, sum[r] += cntr * d;
    if (len > 1) {
        mx[l] = max(mx[l << 1], mx[l << 1 | 1]) + lz[l];
        mx[r] = max(mx[r << 1], mx[r << 1 | 1]) + lz[r];
    }
    cntl += cntr;
    for (l >>= 1; l; l >>= 1) {
        sum[l] += cntl * d;
        mx[l] = max(mx[l << 1], mx[l << 1 | 1]) + lz[l];
    }
}

ll qsum(int l, int r) {
    ll res = 0, len = 1, cntl = 0, cntr = 0;
    for (l += N, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        res += cntl * lz[l] + cntr * lz[r];
        if (~l & 1)
            res += sum[l ^ 1], cntl += len;
        if (r & 1)
            res += sum[r ^ 1], cntr += len;
    }
    res += cntl * lz[l] + cntr * lz[r];
    cntl += cntr;
    for (l >>= 1; l; l >>= 1)
        res += cntl * lz[l];
    return res;
}

ll qmax(int l, int r) {
    ll maxl = -INF, maxr = -INF;
    for (l += N, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        maxl += lz[l], max[r] += lz[r];
        if (~l & 1)
            maxl = max(maxl, mx[l ^ 1]);
        if (r & 1)
            maxr = max(maxr, mx[r ^ 1]);
    }
    maxl = max(maxl + lz[l], maxr + lz[r]);
    for (l >>= 1; l; l >>= 1)
        maxl += lz[l];
    return maxl;
}

