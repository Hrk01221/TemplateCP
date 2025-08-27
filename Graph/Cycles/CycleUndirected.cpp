vector<vector<int>>graph(N+1);
vector<int>vis,parent;
bool dfs(int s,int par){
   vis[s] = 1;
   for(auto u : graph[s]){
      if(u==par)continue;
      if(vis[u]){
         st = u;
         ed = s;
         return true;
      }
      parent[u] = s;
      if(dfs(u,s))return true;
   }
   return false;
}
void solve(int tc){
   parent.assign(n+1,-1);
   vis.assign(n+1,false);
   st = -1;
   ...input graph...
   for(int i=1;i<=n;i++){
      if(!vis[i] && dfs(i,parent[i]))break;
   }
   if(st == -1) cout << "IMPOSSIBLE" << nline;
   else{
      vector<int>cycle;
      int v = ed
      cycle.pb(st);
      while(v!=st){
         cycle.pb(v);
         v = parent[v];
      }
      cycle.pb(st);
}
 
