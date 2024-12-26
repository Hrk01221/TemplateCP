void dfs(int v,vector<int>&vis,vector<int>adj[],stack<int>&st){
    vis[v]=1;
    for(auto it : adj[v]){
        if(!vis[it]){
            dfs(it,vis,adj,st);
        }
    }
    st.push(v);
}
vector<vector<int>>scc_list;
vector<int>all_scc;
void dfs(int v,vector<int>&vis,vector<int>rev_adj[]){
    vis[v]=1;
    all_scc.pb(v);
    for(auto it : rev_adj[v]){
        if(!vis[it])
            dfs(it,vis,rev_adj);
    }
}
int Kosaraju(int V,vector<int>adj[]){ // 1 based
   vector<int>vis(V+1,0);
   stack<int>st;
   for(int i=1;i<=V;i++){
        if(!vis[i])dfs(i,vis,adj,st);
   }
   vector<int>rev_adj[V+1];
   for(int i=1;i<=V;i++){
        vis[i]=0;
        for(auto it : adj[i]){
            rev_adj[it].pb(i);
        }
   }
   int scc=0;
   while(!st.empty()){
        int v = st.top();
        st.pop();
        if(!vis[v]){
            scc++;
            dfs(v,vis,rev_adj);
            scc_list.pb(all_scc);
            all_scc.clear();
        }
   }
   return scc;
}