const int N = 1e5 + 1;
int sz[N];
vector<vector<int>>tree;
vector<vector<int>>sub;
void get_sz(int v, int par) {
    sz[v] = 1;
    for (auto &x : tree[v]) {
        if (x != par) {
            get_sz(x, v);
            sz[v] += sz[x];
        }
    }
}
void add(int x) {}
void del(int x){}
void dfs(int v, int par, bool keep) {
    int mx = 0 , bc = -1;
    for (auto &x : tree[v]) {
        if (x != par && mx < sz[x])
            mx = sz[x] , bc = x;
    }
    for(auto &x : tree[v]){
        if(x!=par && x != bc)
            dfs(x,v,0);
    }
    if (bc != -1) {
        dfs(bc , v , 1);
        swap(sub[v] , sub[bc]);
    }
    sub[v].push_back(v);
    add(v);
    for (auto &x : tree[v]) {
        if (x != par && x != bc) {
            for(auto &y : sub[x]){
                add(y);
                sub[v].push_back(y);
            }
        }
    }
    // answer for v here
    if(!keep){
        for(auto &x : sub[v]){
            del(x);
        }
    }
}
void init(int n){
    tree.resize(n + 1);
    sub.resize(n + 1);
}
/*
    get_sz(1, 0);
    dfs(1,0,1); keeps root data
    dfs(1,0,0); does not keeps root data
*/
