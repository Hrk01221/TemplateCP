const int MaxN = 2e5 + 1;
vector<int>root(MaxN);
struct PST {
#define lc t[cur].l
#define rc t[cur].r
    struct node {
        int l = 0, r = 0, val = 0;
        node(int _l = 0, int _r = 0, int _val = 0): l(_l), r(_r), val(_val) {}
    } t[22 * MaxN];
    int T = 0;
    int build(int b, int e) {
        int cur = ++T;
        if (b == e) return cur;
        int mid = (b + e) >> 1;
        lc = build(b, mid);
        rc = build(mid + 1, e);
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }
    int update(int pre, int b, int e, int i, int v) {
        int cur = ++T;
        t[cur] = t[pre];
        if (b == e) {
            t[cur].val += v;
            return cur;
        }
        int mid = b + e >> 1;
        if (i <= mid) {
            rc = t[pre].r;
            lc = update(t[pre].l, b, mid, i, v);
        } else {
            lc = t[pre].l;
            rc = update(t[pre].r, mid + 1, e, i, v);
        }
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }
    int query(int pre, int b, int e, int l, int r) {
        if (r < b or e < l)return 0;
        if (l <= b and e <= r)return t[pre].val;
        int mid = (b + e) >> 1;
        int left = query(t[pre].l, b, mid, l, r);
        int right = query(t[pre].r, mid + 1, e, l, r);
        return left + right;
    }
    void reset(int n) {
        T = 0;
        for (int i = 0; i < MaxN; ++i)root[i] = 0;
        root[0] = build(1, n);
    }
} t;
