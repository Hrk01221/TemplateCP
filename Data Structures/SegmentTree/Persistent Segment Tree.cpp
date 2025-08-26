struct node {
    node *l, *r;
    int val;
    node(int v = 0) : l(nullptr), r(nullptr), val(v) {}
};
node *root[N];
struct PersistentSegTree {
    int n;
    PersistentSegTree(int _n):n(_n){
        root[0] = build(1,n);//version 0
    }
    int merge(int a, int b) {return a + b;}
    node* build(int lo, int hi) {//init with empty array
        if (lo == hi)return new node();
        int mid = (lo + hi) >> 1;
        node *curr = new node();
        curr->l = build(lo, mid);
        curr->r = build(mid + 1, hi);
        curr->val = merge(curr->l->val , curr->r->val);
        return curr;
    }
    //update the version accordingly
    void update(int version,int idx,int val){
        root[version] = update(root[version-1],1,n,idx,val);
    }
    //update and return the new tree
    node* update(node* prev, int lo, int hi, int idx, int val) {
        if (lo == hi)return new node(prev->val + val);
        int mid = (lo + hi) >> 1;
        node* curr = new node();
        if (idx <= mid) {
            curr->l = update(prev->l, lo, mid, idx, val);
            curr->r = prev->r;
        }
        else {
            curr->l = prev->l;
            curr->r = update(prev->r, mid + 1, hi, idx, val);
        }
        curr->val = merge(curr->l->val, curr->r->val);
        return curr;
    }
    int query(node *curr,int lo,int hi,int l,int r){
        if(r < lo or hi < l)return 0;
        if(l<=lo and hi<=r)return curr->val;
        int mid = (lo + hi)>>1;
        int left = query(curr->l,lo,mid,l,r);
        int right = query(curr->r,mid+1,hi,l,r);
        return merge(left,right);
    }
    //return kth number in a range
    int query(node* prev,node *curr,int lo,int hi,int k){
        if(lo==hi)return lo;
        int sum = curr->l->val - prev->l->val;
        int mid = (lo+hi)>>1;
        if(k <= sum)return query(prev->l,curr->l,lo,mid,k);
        else return query(prev->r,curr->r,mid+1,hi,k-sum);
    }
};
