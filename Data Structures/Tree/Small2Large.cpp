multiset<int>dfs(int v,int p){
    multiset<int>s;
    s.insert(value[v]);
    for(auto u : tree[v]){
        if(u==p) continue;
        auto t = dfs(u,v);
        if(t.size() > s.size())
            swap(s,t);
        for(auto i : t)s.insert(i);
    }
    ans[v] = *s.rbegin();
}
