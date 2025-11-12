multiset<int>* ms[N];
void dfs(int u, int p) {
    ms[u] = new multiset<int>();
    ms[u]->insert(value[u]);
    for (int v : g[u]) if (v != p) {
        dfs(v, u);
        if (ms[v]->size() > ms[u]->size())
            swap(ms[u], ms[v]);
        for (int x : *ms[v])
            ms[u]->insert(x);
    }
    ans[u] = *ms[u]->rbegin();
}
