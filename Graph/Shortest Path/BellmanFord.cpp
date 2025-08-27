struct node{
    int u,v,w;
    node(int _u=-1,int _v=-1 ,int _w=0):u(_u),v(_v),w(_w){};
};
vector<int>dis,par;
void bellmanFord(int n,vector<node>&edges){
    dis.assign(n+1,1e18);par.assign(n+1,-1);
    int neg_cycle_last_node;
    for(int i=0;i<n;i++){
        neg_cycle_last_node = -1;
        auto [u,v,w] = edges[i];
        if(dis[v] > dis[u]+w){
            dis[v] = dis[u]+w;
            par[v] = u;
            neg_cycle_last_node = v;
        }
    }
    if(neg_cycle_last_node==-1)cout << "NO NEGATIVE CYCLE" << endl;
    else {
        ...print path...
    }
}
