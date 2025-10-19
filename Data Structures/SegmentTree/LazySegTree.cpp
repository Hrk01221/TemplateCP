struct node {
    int val;
    node(int v = 0) : val(v) {}
};

node combine(const node &a, const node &b) {
    return node(a.val + b.val); 
}

struct SegmentTree {
    int n;
    vector<int> lazyAdd, lazyAssign;
    vector<bool> assignFlag;
    vector<node> tree, a;

    SegmentTree(vector<node> arr) {
        n = arr.size() - 1; // 1-based
        a = arr;
        lazyAdd.assign(4 * n + 5, 0);
        lazyAssign.assign(4 * n + 5, 0);
        assignFlag.assign(4 * n + 5, false);
        tree.assign(4 * n + 5, node());
        build(1, 1, n);
    }

    inline void applyAssign(int idx, int start, int end, int val) {
        tree[idx].val = (end - start + 1) * val; //for sum
        //tree[idx].val = val; // for max/min
        lazyAssign[idx] = val;
        lazyAdd[idx] = 0; 
        assignFlag[idx] = true;
    }

    inline void applyAdd(int idx, int start, int end, int val) {
        tree[idx].val += (end - start + 1) * val; //for sum
        //tree[idx].val += val; // for max/min
        if (assignFlag[idx]) lazyAssign[idx] += val; 
        else lazyAdd[idx] += val;
    }

    void push(int idx, int start, int end) {
        if (start == end) return;
        if (assignFlag[idx] || lazyAdd[idx] != 0) {
            int mid = (start + end) / 2;
            int L = idx * 2, R = idx * 2 + 1;

            if (assignFlag[idx]) {
                applyAssign(L, start, mid, lazyAssign[idx]);
                applyAssign(R, mid + 1, end, lazyAssign[idx]);
                assignFlag[idx] = false;
                lazyAssign[idx] = 0;
            }

            if (lazyAdd[idx] != 0) {
                applyAdd(L, start, mid, lazyAdd[idx]);
                applyAdd(R, mid + 1, end, lazyAdd[idx]);
                lazyAdd[idx] = 0;
            }
        }
    }

    void build(int idx, int start, int end) {
        if (start == end) {
            tree[idx] = a[start];
            return;
        }
        int mid = (start + end) / 2;
        build(idx * 2, start, mid);
        build(idx * 2 + 1, mid + 1, end);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void rangeAdd(int l, int r, int val) { rangeAdd(1, 1, n, l, r, val); }
    void rangeAssign(int l, int r, int val) { rangeAssign(1, 1, n, l, r, val); }
    node query(int l, int r) { return query(1, 1, n, l, r); }

    void rangeAdd(int idx, int start, int end, int l, int r, int val) {
        if (l > r || r < start || end < l) return;
        if (l <= start && end <= r) {
            applyAdd(idx, start, end, val);
            return;
        }
        push(idx, start, end);
        int mid = (start + end) / 2;
        rangeAdd(idx * 2, start, mid, l, r, val);
        rangeAdd(idx * 2 + 1, mid + 1, end, l, r, val);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void rangeAssign(int idx, int start, int end, int l, int r, int val) {
        if (l > r || r < start || end < l) return;
        if (l <= start && end <= r) {
            applyAssign(idx, start, end, val);
            return;
        }
        push(idx, start, end);
        int mid = (start + end) / 2;
        rangeAssign(idx * 2, start, mid, l, r, val);
        rangeAssign(idx * 2 + 1, mid + 1, end, l, r, val);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

    node query(int idx, int start, int end, int l, int r) {
        if (l > r || r < start || end < l) return node(0);
        push(idx, start, end);
        if (l <= start && end <= r) return tree[idx];
        int mid = (start + end) / 2;
        node left = query(idx * 2, start, mid, l, r);
        node right = query(idx * 2 + 1, mid + 1, end, l, r);
        return combine(left, right);
    }
};
