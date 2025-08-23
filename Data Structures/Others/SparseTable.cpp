struct SparseTable {
    int n;
    vector<int> A, Log;
    vector<vector<int>> M;
    SparseTable(const vector<int>& arr) {
        n = arr.size();
        A = arr;
        A.insert(A.begin(), 0);// make it 1-based
        Log.assign(n+1, 0);
        int maxLog = 32 - __builtin_clz(n);
        M.assign(n+1, vector<int>(maxLog+1, 0));
        build();
    }
    void build() {
        for(int i=1; i<=n; i++) M[i][0] = A[i];
        for(int i=2; i<=n; i++) Log[i] = Log[i-1] + !(i & (i-1));
        for(int j=1; (1<<j)<=n; j++) {
            for(int i=1; i + (1<<j) -1 <= n; i++)
                M[i][j] = min(M[i][j-1], M[i + (1<<(j-1))][j-1]);
        }
    }
    int query(int l, int r) { // 1-based
        int k = Log[r-l+1];
        return min(M[l][k], M[r-(1<<k)+1][k]);
    }//O(1) queries
};