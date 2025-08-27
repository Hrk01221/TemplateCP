const int N = 2e5;
vector<int>graph[N+10],dis(N+10);
void dfs(int v,int par,int cnt){
    for(auto it : graph[v]){
        if(it!=par){
            dis[it] = cnt+1;
            dfs(it,v,cnt+1);
        }
    }
}
int diameter(int n){
    dfs(1,0,0);
    int a,mx=0;
    for(int i=1;i<=n;i++){   
        if(dis[i]>mx){mx = dis[i],a=i};
        dis[i]=0;
    }
    dfs(a,0,0);
    return *max_element(dis);
}