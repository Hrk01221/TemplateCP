void dfs1(int v, vector<int>& vis, vector<vector<int>>& adj, stack<int>& st) {
    vis[v] = 1;
    for (auto it : adj[v]) {
        if (!vis[it])
            dfs1(it, vis, adj, st);
    }
    st.push(v);
}
vector<vector<int>> scc_list;//stores scc in topological order
vector<int> all_scc;
void dfs2(int v, vector<int>& vis, vector<vector<int>>& rev_adj) {
    vis[v] = 1;
    all_scc.push_back(v);
    for (auto it : rev_adj[v]) {
        if (!vis[it])
            dfs2(it, vis, rev_adj);
    }
}
int Kosaraju(int V, vector<vector<int>>& adj) { // 1 based
    vector<int> vis(V + 1, 0);
    stack<int> st;
    for (int i = 1; i <= V; i++)
        if (!vis[i]) dfs1(i, vis, adj, st);
    vector<vector<int>> rev_adj(V + 1);
    for (int i = 1; i <= V; i++) {
        vis[i] = 0;
        for (auto it : adj[i]) 
            rev_adj[it].push_back(i);
    }
    int scc = 0;
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (!vis[v]) {
            scc++;
            dfs2(v, vis, rev_adj);
            scc_list.push_back(all_scc);
            all_scc.clear();
        }
    }
    return scc;
}