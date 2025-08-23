struct SegTreeBeats {//0-based
    struct Node {
        int max1, max2, cnt_max;
        int min1, min2, cnt_min;
        long long sum;
    };
    int n;
    vector<Node> st;
    SegTreeBeats(int n): n(n), st(4*n) {}
    Node make_leaf(int val) {
        return {val, -INF, 1, val, INF, 1, val};
    }
    Node merge(Node L, Node R) {
        Node res;
        res.sum = L.sum + R.sum;
        // merge max
        if (L.max1 == R.max1) {
            res.max1 = L.max1;
            res.cnt_max = L.cnt_max + R.cnt_max;
            res.max2 = max(L.max2, R.max2);
        } else {
            if (L.max1 < R.max1) swap(L, R);
            res.max1 = L.max1;
            res.cnt_max = L.cnt_max;
            res.max2 = max(L.max2, R.max1);
        }

        // merge min
        if (L.min1 == R.min1) {
            res.min1 = L.min1;
            res.cnt_min = L.cnt_min + R.cnt_min;
            res.min2 = min(L.min2, R.min2);
        } else {
            if (L.min1 > R.min1) swap(L, R);
            res.min1 = L.min1;
            res.cnt_min = L.cnt_min;
            res.min2 = min(L.min2, R.min1);
        }
        return res;
    }
    void build(vector<int> &a, int v, int l, int r) {
        if (l == r) {
            st[v] = make_leaf(a[l]);
            return;
        }
        int m = (l+r)/2;
        build(a,v*2,l,m);
        build(a,v*2+1,m+1,r);
        st[v] = merge(st[v*2], st[v*2+1]);
    }
    void build(vector<int> &a) { build(a,1,0,n-1); }
    void push_min(int v, int x) {
        if (st[v].max1 <= x) return;
        st[v].sum -= 1LL * (st[v].max1 - x) * st[v].cnt_max;
        if (st[v].min1 == st[v].max1) st[v].min1 = x;
        else if (st[v].min2 == st[v].max1) st[v].min2 = x;
        st[v].max1 = x;
    }
    void push_max(int v, int x) {
        if (st[v].min1 >= x) return;
        st[v].sum += 1LL * (x - st[v].min1) * st[v].cnt_min;
        if (st[v].max1 == st[v].min1) st[v].max1 = x;
        else if (st[v].max2 == st[v].min1) st[v].max2 = x;
        st[v].min1 = x;
    }
    void push(int v) {
        for (int u : {v*2, v*2+1}) {
            if (st[v].max1 < st[u].max1) push_min(u, st[v].max1);
            if (st[v].min1 > st[u].min1) push_max(u, st[v].min1);
        }
    }
    void range_chmin(int v, int l, int r, int ql, int qr, int x) {
        if (r < ql || qr < l || st[v].max1 <= x) return;
        if (ql <= l && r <= qr && st[v].max2 < x) {
            push_min(v,x);
            return;
        }
        push(v);
        int m = (l+r)/2;
        range_chmin(v*2, l, m, ql, qr, x);
        range_chmin(v*2+1, m+1, r, ql, qr, x);
        st[v] = merge(st[v*2], st[v*2+1]);
    }
    void range_chmax(int v, int l, int r, int ql, int qr, int x) {
        if (r < ql || qr < l || st[v].min1 >= x) return;
        if (ql <= l && r <= qr && st[v].min2 > x) {
            push_max(v,x);
            return;
        }
        push(v);
        int m = (l+r)/2;
        range_chmax(v*2, l, m, ql, qr, x);
        range_chmax(v*2+1, m+1, r, ql, qr, x);
        st[v] = merge(st[v*2], st[v*2+1]);
    }

    long long range_sum(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) return 0;
        if (ql <= l && r <= qr) return st[v].sum;
        push(v);
        int m = (l+r)/2;
        return range_sum(v*2, l, m, ql, qr) + range_sum(v*2+1, m+1, r, ql, qr);
    }
    void range_chmin(int l, int r, int x) { range_chmin(1,0,n-1,l,r,x); }
    void range_chmax(int l, int r, int x) { range_chmax(1,0,n-1,l,r,x); }
    long long range_sum(int l, int r) { return range_sum(1,0,n-1,l,r); }
};