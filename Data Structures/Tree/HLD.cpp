const int MaxN = 2e5 + 10;
int idx;
struct node{
    int val;
    node(int _val = 0){
        val = _val;
    }
};
vector<int>tree[MaxN],sz(MaxN),dep(MaxN),par(MaxN),hv(MaxN);
vector<int>head(MaxN),pos(MaxN);
vector<node>lt,val(MaxN);
struct SegmentTree{ // ALL 1 Based
  int n;
  vector<node>a;
  node *t;
  SegmentTree(vector<node>_a) {
    n = _a.size() - 1;
    a = _a; 
    t = new node[2 * n];
    build();
  }
  inline node combine(node l, node r) {
        return l.val + r.val;
  }
  void build() {
    for(int i = 0; i < n; i++) t[i + n] = a[i+1];
    for(int i = n - 1; i > 0; --i) t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }
  void update(int p, node v) {
    p--;
    for (t[p += n] = v; p >>= 1; ) t[p] = combine(t[p << 1], t[p << 1 | 1]);
  }
  node query(int l, int r) {
    --l;
    bool f1 = 1, f2 = 1;
    node resl, resr;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = f1 ? t[l++] : combine(resl, t[l++]), f1 = 0;
      if(r & 1) resr = f2 ? t[--r] : combine(t[--r], resr), f2 = 0;
    }
    if(f2) return resl;
    if(f1) return resr;
    return combine(resl, resr);
  }
};
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
    head[v] = chain;
    lt[idx] = val[v];
    pos[v] = idx;idx++;
    if(hv[v]!=0)dfs2(hv[v],v,chain);
    for(auto it : tree[v])
        if(it != hv[v] and it != p)dfs2(it,v,it);
}
node query(int a,int b,SegmentTree &seg){
    node ans = node(0);
    while(head[a]!=head[b]){
        if(dep[head[a]] < dep[head[b]])swap(a,b);
        ans = seg.combine(ans,seg.query(pos[head[a]],pos[a]));
        a = par[head[a]];
    }
    if(dep[a] < dep[b])swap(a,b);
    ans = seg.combine(ans,seg.query(pos[b],pos[a]));
    return ans;
}
void change(int nde,node v,SegmentTree &seg){
    seg.update(pos[nde],v);lt[pos[nde]] = v;
}
void reset(int n){
    for(int i=1;i<=n;i++){
        tree[i].clear();
        sz[i] = dep[i] = par[i] = hv[i] = 0;
        head[i] = pos[i] = 0;
        val[i] = node(0);
    }
    lt.assign(n+1,node(0));
}
void hld(){dfs(1,0);idx = 1;dfs2(1,0,1);}
/*
reset(n)
input(val[i])->value written on node
input graph
hld()
SegmentTree seg(lt);
change(node,val,seg)->change the value
query(a,b,seg)->query path from a to b
*/
/*
    https://www.spoj.com/problems/GSS7/
    
    How to do left right merge in query
    node query(int a, int b, SegmentTree &seg) {
    node left = node(0) , right = node(0);
    while(head[a] != head[b]){
        if(dep[head[a]] >= dep[head[b]]){
            node curr = seg.query(pos[head[a]],pos[a]);
            left = combine(curr,left);
            a = par[head[a]];
        }
        else {
            node curr = seg.query(pos[head[b]],pos[b]);
            right = combine(curr,right);
            b = par[head[b]];
        }
    }
    if (dep[a] >= dep[b]) {
        node cur = seg.query(pos[b], pos[a]); 
        left = combine(cur, left);
    } else {
        node cur = seg.query(pos[a], pos[b]); 
        right = combine(cur, right);
    }
    swap(left.mpref,left.msuff);
    return combine(left,right);
}
*/
