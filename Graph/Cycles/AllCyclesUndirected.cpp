vector<int>graph[N+1],par(N+1),color(N+1);
vector<vector<int>>cycle;
void dfs_cycle(int u,int p){
    if(color[u] == 2)return;
    if(color[u]==1){
        int curr = p;
        vector<int>curr_cyc;
        curr_cyc.pb(curr);
        while(curr != u){
            curr = par[curr];
            curr_cyc.pb(curr);
        }
        cycle.pb(curr_cyc);
        return;
    }
    par[u] = p;
    color[u]=1;
    for(auto v : graph[u]){
        if(v==par[u])continue;
        dfs_cycle(v,u);
    }
    color[u]=2;
}