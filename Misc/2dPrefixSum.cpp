struct TwoDPrefixSum{
    vector<vector<int>>pref;
    int n,m;
    TwoDPrefixSum(int n,int m){
        this->n=n;
        this->m=m;
        pref.assign(n+2,vector<int>(m+2,0));
    }
    TwoDPrefixSum(int n,int m,vector<vector<int>>&a){
        this->n=n;
        this->m=m;
        pref=a;
    }
    void update(pii a, pii b ,int val){
        int x1 = a.ff, y1 = a.ss;
        int x2 = b.ff, y2 = b.ss;
        pref[x1][y1] += val;
        pref[x2 + 1][y1] -= val;
        pref[x1][y2 + 1] -= val;
        pref[x2 + 1][y2 + 1] += val;
    }
    void build(){
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                pref[i][j] += pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
            }
        }
    }
    int query(pii a, pii b){
        int val = pref[b.ff][b.ss];
        val -= pref[a.ff - 1][b.ss];
        val -= pref[b.ff][a.ss - 1];
        val += pref[a.ff - 1][a.ss - 1];
        return val;
    }
};