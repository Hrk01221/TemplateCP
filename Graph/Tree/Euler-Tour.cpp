vector<int>st(N+1),ed(N+1);
int timer = 0;
void eulerTour(int v,int par){
    st[v]=timer++;
    for(auto u:graph[v])
        if(u!=par)eulerTour(u,v);
    ed[v] = timer;
}