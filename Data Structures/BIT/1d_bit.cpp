template <class T>
struct Fenwick {//1 based
    int n;
    vector<T> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_) { init(n_); }
    void init(int n_) { n = n_; bit.assign(n + 1, T(0)); }
    // add value 'delta' at position idx
    void add(int idx, T delta) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += delta;
    }
    // prefix sum [1..idx]
    T sum_prefix(int idx) const {
        T res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    // range sum [l..r]
    T sum(int l, int r) const {
        if (r < l) return 0;
        return sum_prefix(r) - sum_prefix(l - 1);
    }
};//Fenwick<int>fw(n);