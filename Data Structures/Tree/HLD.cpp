const int MaxN = 2e5 + 10;
int idx;
vector<int>tree[MaxN],sz(MaxN),dep(MaxN),par(MaxN),hv(MaxN);
vector<int>head(MaxN),lt,pos(MaxN),val(MaxN);
//paste Segtree here***
void dfs(int v,int p){
    sz[v] = 1;
    for(auto it : tree[v]){
        if(it != p){
            dep[it] = dep[v] + 1;par[it] = v;
            dfs(it,v);sz[v] += sz[it];
            if(sz[it] > sz[hv[v]]) hv[v] = it;
        }
    }
}
void dfs2(int v,int p,int chain){
    head[v] = chain;lt[idx] = val[v];
    pos[v] = idx;idx++;
    if(hv[v]!=0)dfs2(hv[v],v,chain);
    for(auto it : tree[v])
        if(it != hv[v] and it != p)dfs2(it,v,it);
}
void reset(int n){
    for(int i=1;i<=n;i++){
        tree[i].clear();
        sz[i] = dep[i] = par[i] = hv[i] = 0;
        head[i] = pos[i] = val[i] = 0;
    }
    lt.assign(n+1,0);
}
void hld(){dfs(1,0);idx = 1;dfs2(1,0,1);}
int query(int a,int b,SegmentTree &seg){
    int ans = 0;
    while(head[a]!=head[b]){
        if(dep[head[a]] < dep[head[b]])swap(a,b);
        ans = max(ans,seg.query(pos[head[a]],pos[a]));
        a = par[head[a]];
    }
    if(dep[a] < dep[b])swap(a,b);
    ans = max(ans,seg.query(pos[b],pos[a]));
    return ans;
}
void change(int node,int v,SegmentTree &seg){
    seg.update(pos[node],v);lt[pos[node]] = v;
}
/*
reset(n)
input(val[i])->value written on node
input graph
hld()
SegmentTree seg(lt);
change(node,val,seg)->change the value
query(a,b,seg)->query path from a to b
*/