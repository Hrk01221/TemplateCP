...Add DSU...
struct node{
    int u,v,w;
    node(int _u=-1,int _v=-1 ,int _w=0):u(_u),v(_v),w(_w){};
    bool operator < (const node &a) const{
        return w < a.w;
    }
};
int krushkal(int n,vector<node>edges){
    sort(all(edges));
    init(n);
    int ans = 0;
    for(auto [u,v,w] : edges){
        if(find_set(u)!=find_set(v)){
            ans += w;
            union_sets(u,v);
        }
    }
    return get_size(1)==n ? ans : -1;
}