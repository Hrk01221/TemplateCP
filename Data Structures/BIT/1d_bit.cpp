struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int sum(int idx) {
        int s = 0;
        while (idx > 0) {
            s += bit[idx];
            idx -= idx & -idx;
        }
        return s;
    }

    int kth(int k) {
        int pos = 0;

        int pw = 1;
        while (pw <= n) pw <<= 1;
        pw >>= 1;

        while (pw) {
            if (pos + pw <= n && bit[pos + pw] < k) {
                k -= bit[pos + pw];
                pos += pw;
            }
            pw >>= 1;
        }

        return pos + 1;
    }
};
/*
    Fenwick fw(n);
    fw.bit.assign(n + 1, 0);
    fw.add(x,1);
*/
