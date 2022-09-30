struct IncrementalMinSum {
  multiset <int, greater <int>> in;
  multiset <int> out;
  ll sum; int cap;
  DS () : sum(0), cap(0) {}
  void enlarge() {
    if (!out.empty()) {
      int mx = *out.begin();
      sum += mx, in.insert(mx), out.erase(out.begin());
    }
    cap++;
  }
  void insert(int x) {
    if (!cap) {
      out.insert(x);
      return;
    }
    if (in.size() < cap) {
      in.insert(x), sum += x;
      return;
    }
    int mx = *in.begin();
    if (x < mx) {
      sum -= mx, out.insert(mx), in.erase(in.begin());
      sum += x, in.insert(x);
    } else {
      out.insert(x);
    }
  }
  void erase(int x) {
    if (out.find(x) != out.end()) {
      out.erase(out.lower_bound(x));
    } else {
      in.erase(in.lower_bound(x)), sum -= x;
      if (!out.empty()) {
        int mx = *out.begin();
        sum += mx, out.erase(out.begin()), in.insert(mx);
      }
    }
  }
};