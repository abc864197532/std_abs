vector <Pt> ConvexHull(vector <Pt> pt) {
    int n = pt.size();
    sort(all(pt), [&](Pt a, Pt b) {return a.x == b.x ? a.y < b.y : a.x < b.x;});
    auto check = [&](Pt a, Pt b, Pt c) {return ((a - b) ^ (a - c)) <= 0;};
    vector <Pt> ans = {pt[0]};
    for (int t : {0, 1}) {
        int m = ans.size();
        for (int i = 1; i < n; ++i) {
            while (ans.size() > m && check(ans[ans.size() - 2], ans.back(), pt[i]))
                ans.pop_back();
            ans.push_back(pt[i]);
        }
        reverse(all(pt));
    }
    ans.pop_back();
    return ans;
}