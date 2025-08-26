
const int MaxN = 1e4 + 10;
int idx;
vector<int>tree[MaxN],cost[MaxN],sz(MaxN),dep(MaxN),par(MaxN),hv(MaxN);
vector<int>head(MaxN),lt,pos(MaxN),val(MaxN);

struct SegmentTree{ // ALL 1 Based
  int n;
  vector<int>a;
  int *t;
  SegmentTree(vector<int>_a) {
    n = _a.size() - 1;
    a = _a; 
    t = new int[2 * n];
    build();
  }
  inline int combine(int l, int r) {
        return max(l,r);
  }

  void build() {
    for(int i = 0; i < n; i++) t[i + n] = a[i+1];
    for(int i = n - 1; i > 0; --i) t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }

  void update(int p, int v) {
    p--;
    for (t[p += n] = v; p >>= 1; ) t[p] = combine(t[p << 1], t[p << 1 | 1]);
  }

  int query(int l, int r) {
    --l;
    bool f1 = 1, f2 = 1;
    int resl, resr;
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
            dep[it] = dep[v] + 1;
            par[it] = v;
            dfs(it,v);
            sz[v] += sz[it];
            if(sz[it] > sz[hv[v]]){
                hv[v] = it;
            }
        }
    }
}
void dfs2(int v,int p,int chain){
    head[v] = chain;
    lt[idx] = val[v];
    pos[v] = idx;
    idx++;
    if(hv[v]!=0){
        dfs2(hv[v],v,chain);
    }
    for(auto it : tree[v]){
        if(it != hv[v] and it != p){
            dfs2(it,v,it);
        }
    }
}
void reset(int n){
    for(int i=1;i<=n;i++){
        tree[i].clear();
        cost[i].clear();
        sz[i] = dep[i] = par[i] = hv[i] = 0;
        head[i] = pos[i] = val[i] = 0;
    }
    lt.assign(n+1,0);
}
void hld(){
    dfs(1,0);
    idx = 1;
    dfs2(1,0,1);
}
int query(int a,int b,SegmentTree &seg){
    int ans = 0;
    while(head[a]!=head[b]){
        if(dep[head[a]] < dep[head[b]]){
            swap(a,b);
        }
        ans = max(ans,seg.query(pos[head[a]],pos[a]));
        a = par[head[a]];
    }
    if(dep[a] < dep[b])swap(a,b);
    if(pos[b]+1 <= pos[a])ans = max(ans,seg.query(pos[b]+1,pos[a]));
    return ans;
}
void change(int node,int v,SegmentTree &seg){
   seg.update(pos[node],v);
}
struct node{
    int a,b,c;
    node(int _id,int _cost,int _k){
        a = _id;
        b = _cost;
        c = _k;
    }
};
void solve(int tc){
    int n; cin >> n;
    reset(n);
    vector<node>edges;
    for(int i=0;i<n-1;i++){
        int x,y,z; cin >> x >> y >> z;
        tree[x].pb(y);
        tree[y].pb(x);
        cost[x].pb(z);
        cost[y].pb(z);
        edges.pb(node(x,y,z));
    }
    val[1] = 0;
    function<void(int,int)>gen = [&] (int v,int p){
        for(int i=0;i<tree[v].size();i++){
            int node = tree[v][i];
            int cst = cost[v][i];
            if(node==p)continue;
            val[node] = cst;
            gen(node,v);
        }
    };
    gen(1,0);
    hld();
    SegmentTree seg(lt);
    while(1){
        string s; cin >> s;
        if(s=="DONE")break;
        if(s=="CHANGE"){
            int i , x; cin >> i >> x;
            i--;
            int u = edges[i].a;
            int v = edges[i].b;
            if(dep[u] > dep[v]) {
                change(u,x,seg);
            }
            else {
                change(v,x,seg);
            }
        }
        else {
            int x,y; cin >> x >> y;
            cout << query(x,y,seg) << endl;
        }
    }
}
