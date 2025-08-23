struct CentroidDecomposition{
    vector<set<int>> tree;
    vector<int>dad,sub;
    int root = -1;
    CentroidDecomposition(vector<vector<int>>&_tree){
        int n = _tree.size();
        tree.resize(n);
        for(int i=1;i<n;i++)
            for(int j=0;j<_tree[i].size();j++)
                tree[i].insert(_tree[i][j]);
        dad.resize(n);sub.resize(n);
        build(1,-1);
    }
    void build(int u,int p){
        int n = dfs(u,p);
        int centroid = dfs(u,p,n);
        if(root==-1)root = centroid;
        if(p==-1)p = centroid;
        dad[centroid] = p;
        vector<int> neighbors(tree[centroid].begin(),tree[centroid].end());
        for(auto v : neighbors){
            tree[centroid].erase(v);
            tree[v].erase(centroid);
            build(v,centroid);
        }
    }
    int dfs(int u,int p){
        sub[u] = 1;
        for(auto v : tree[u])
            if(v!=p)sub[u] += dfs(v,u);
        return sub[u];
    }
    int dfs(int u,int p,int n){
        for(auto v : tree[u])
            if(v!=p and sub[v] > n/2)
                return dfs(v,u,n);
        return u;
    }
};