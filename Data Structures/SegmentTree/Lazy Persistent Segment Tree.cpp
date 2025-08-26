struct node {
    node *l, *r;
    int val, lazy;
    node(int v = 0) : l(nullptr), r(nullptr), val(v), lazy(0) {}
};
node *root[N];
struct PersistentSegTree {
    int n;
    PersistentSegTree(int _n,vector<int>&a):n(_n){
        root[0] = build(1,n,a);
    }
    int merge(int a, int b) {return a + b;}
    node* build(int lo, int hi,vector<int>&a) {
        if (lo == hi) return new node(a[lo]);
        int mid = (lo + hi) >> 1;
        node *curr = new node();
        curr->l = build(lo, mid,a);
        curr->r = build(mid + 1, hi,a);
        curr->val = merge(curr->l->val , curr->r->val);
        return curr;
    }
    void update(int version,int l,int r,int val){
        root[version] = update(root[version-1],1,n,l,r,val);
    }
    node* apply(node* prev, int lo, int hi, int val){
        node* curr = new node();
        curr->val = prev->val + (hi - lo + 1) * val;
        curr->lazy = prev->lazy + val;
        curr->l = prev->l;
        curr->r = prev->r;
        return curr;
    }
    node* push(node* prev, int lo, int hi){
        if(prev->lazy == 0) return prev;
        node* curr = new node();
        int mid = (lo + hi) >> 1;
        curr->l = apply(prev->l, lo, mid, prev->lazy);
        curr->r = apply(prev->r, mid+1, hi, prev->lazy);
        curr->val = merge(curr->l->val, curr->r->val);
        curr->lazy = 0;
        return curr;
    }
    node* update(node* prev, int lo, int hi, int l, int r, int val){
        if(r < lo || hi < l) return prev;
        if(l <= lo && hi <= r) return apply(prev, lo, hi, val);

        node* pushed = push(prev, lo, hi);
        node* curr = new node();
        int mid = (lo + hi) >> 1;
        curr->l = update(pushed->l, lo, mid, l, r, val);
        curr->r = update(pushed->r, mid+1, hi, l, r, val);
        curr->val = merge(curr->l->val, curr->r->val);
        return curr;
    }
    int query(node* curr, int lo, int hi, int l, int r){
        if(!curr || r < lo || hi < l) return 0;
        if(l <= lo && hi <= r) return curr->val;
        node* pushed = push(curr, lo, hi);
        int mid = (lo + hi) >> 1;
        int left = query(pushed->l, lo, mid, l, r);
        int right = query(pushed->r, mid+1, hi, l, r);
        return merge(left, right);
    }
};
