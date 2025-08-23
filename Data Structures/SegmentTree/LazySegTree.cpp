struct Node {
    int sum; int mn, mx; 
    Node(int s=0,int mi=INT_MAX,int ma=INT_MIN):sum(s),mn(mi),mx(ma){}
    friend Node merge(const Node &a,const Node &b){
        return Node(a.sum+b.sum,min(a.mn,b.mn),max(a.mx,b.mx));
    }
};
struct Update{int add; Update(int x=0):add(x){} 
    void combine(const Update &u){ add += u.add; } 
};
struct SegTree {
    int n; vector<Node> t; vector<Update> lazy;
    SegTree(int sz){ n=sz; t.assign(4*n,Node()); lazy.assign(4*n,Update()); }
    void build(const vector<int> &a){ build(1,0,n-1,a); }
    void upd(int l,int r,int v){ update(1,0,n-1,l,r,Update(v)); }
    Node qry(int l,int r){ return query(1,0,n-1,l,r); }
    void apply(int node,int s,int e,const Update &u){
        t[node].sum += (e-s+1)*u.add; t[node].mn += u.add; t[node].mx += u.add;
        if(s!=e){ lazy[2*node].combine(u); lazy[2*node+1].combine(u); }
    }
    void prop(int node,int s,int e){
        if(lazy[node].add){ 
            apply(node,s,e,lazy[node]);
            lazy[node]=Update();
        } 
    }
    void build(int node,int s,int e,const vector<int> &a){
        if(s==e){ t[node]=Node(a[s],a[s],a[s]); return; }
        int m=(s+e)/2; build(2*node,s,m,a); build(2*node+1,m+1,e,a);
        t[node]=merge(t[2*node],t[2*node+1]);
    }

    void update(int node,int s,int e,int l,int r,const Update &u){
        prop(node,s,e); if(r<s||e<l) return;
        if(l<=s && e<=r){ apply(node,s,e,u); return; }
        int m=(s+e)/2; update(2*node,s,m,l,r,u); update(2*node+1,m+1,e,l,r,u);
        t[node]=merge(t[2*node],t[2*node+1]);
    }
    Node query(int node,int s,int e,int l,int r){
        prop(node,s,e); if(r<s||e<l) return Node();
        if(l<=s && e<=r) return t[node];
        int m=(s+e)/2;
        return merge(query(2*node,s,m,l,r),query(2*node+1,m+1,e,l,r));
    }
};//0-based