struct LCA{
    int n,mxe;
    vector<int>dep,vis;
    vector<vector<int>>tree,up;
    LCA(vector<vector<int>>&_tree){
        tree = _tree;
        n = tree.size();
        mxe = log2(n) + 5;
        up.resize(n,vector<int>(mxe,-1));
        dep.resize(n);
        vis.resize(n);
        dfs(1,-1,0);
        for(int i=1;i<mxe;i++){
        for(int j=1;j<n;j++){
            if(up[j][i-1]!=-1)
                up[j][i] = up[up[j][i-1]][i-1];
            }
        }
    }
    void dfs(int v,int p,int d){
        vis[v] = 1;
        dep[v] = d;
        up[v][0] = p;
        for(auto it : tree[v])
            if(!vis[it])
                dfs(it,v,d+1);
    }
    int lift(int node,int dist){
        for(int l=0;l<mxe;l++){
            if(node!=-1 and (dist & (1ll<<l)))
                node = up[node][l];
        }
        return node;
    }
    int lca(int a,int b){
        a = lift(a,dep[a]-min(dep[a],dep[b]));
        b = lift(b,dep[b]-min(dep[a],dep[b]));
        if(a==b)return a;
        for(int l=mxe-1;l>=0;l--)
            if(up[a][l] != up[b][l]){
                a = up[a][l];
                b = up[b][l];
            }
        return up[a][0];
    }
    int distance(int a,int b){
        return dep[a] + dep[b] - 2 * dep[lca(a,b)];
    }
};
