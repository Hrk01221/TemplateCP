struct EdmondKarp {// O(VE^2)
    int n;
    vector<vector<int>>cap,g;
    vector<int>p;
    EdmondKarp(int _n){
        n = _n;
        cap.assign(n+1,vector<int>(n+1,0));
        g.assign(n+1,vector<int>());
    }
     void addEdge(int u, int v, int c) {
        g[u].push_back(v);
        g[v].push_back(u);
        cap[u][v] += c;
    }
    int bfs(int s,int t){
        p.assign(n+1,0);
        p[s] = -1;
        queue<pii>q;
        q.push({s,INF});
        while(!q.empty()){
            auto [u,bn] = q.front();
            q.pop();
            for(int v : g[u]){
                if(!p[v]&&cap[u][v]){
                    p[v] = u;
                    if(v==t)return min(bn,cap[u][v]);
                    q.push({v,min(bn,cap[u][v])});
                }
            }
        }
        return 0;
    }
    int maxflow(int s,int t){
        int flow = 0 , aug = 0;
        while(aug = bfs(s,t)){
            flow += aug;
            int u = t;
            while(u != s){
                cap[p[u]][u] -= aug;
                cap[u][p[u]] += aug;
                u = p[u];
            }
        }
        return flow;
    }
};