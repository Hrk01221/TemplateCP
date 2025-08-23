struct SegmentTree{ // ALL 1 Based
  int n;
  vector<int>a;
  int *t;
  SegmentTree(vector<int>_a) {
    n = _a.size() - 1;
    a = _a; 
    t = new int[2 * n];
    build();
  }
  inline int combine(int l, int r) {
        return max(l,r);
  }
  void build() {
    for(int i = 0; i < n; i++) t[i + n] = a[i+1];
    for(int i = n - 1; i > 0; --i) t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }
  void update(int p, int v) {
    p--;
    for (t[p += n] = v; p >>= 1; ) t[p] = combine(t[p << 1], t[p << 1 | 1]);
  }
  int query(int l, int r) {
    --l;
    bool f1 = 1, f2 = 1;
    int resl, resr;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = f1 ? t[l++] : combine(resl, t[l++]), f1 = 0;
      if(r & 1) resr = f2 ? t[--r] : combine(t[--r], resr), f2 = 0;
    }
    if(f2) return resl;
    if(f1) return resr;
    return combine(resl, resr);
  }
};