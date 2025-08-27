stack<int>st;
vector<int>graph[N+1],vis(N+1),dfs_order(N+1),representative_dfs_order(N+1),claimed(N+1);
vector<int>gg[N+1];
int timer;
void find_sccs(int x){
    vis[x] = 1;
    st.push(x);
    dfs_order[x] = timer;
    timer++;
    representative_dfs_order[x] = dfs_order[x];
    for(auto y : graph[x]){
        if(!vis[y]){
            find_sccs(y);
        }
        if(!claimed[y])
            representative_dfs_order[x] = min(representative_dfs_order[x], representative_dfs_order[y]);
    }
    if(representative_dfs_order[x] == dfs_order[x]){
        int popped_value = -1;
        while(popped_value != x){
            popped_value = st.top();
            st.pop();
            cout << popped_value << " ";
            claimed[popped_value] = 1;
        }
        cout << endl;
    }
}
void allScc(int n){
    timer = 0;
    for(int i=1;i<=n;i++){
        if(!vis[i])find_sccs(i);
    }
}