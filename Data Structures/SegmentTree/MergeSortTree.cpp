class MergeSortTree
{//0 based
public:
    int n;
    vector<int>arr;
    vector<multiset<int>>tree;
    MergeSortTree(vector<int>&v){
        n = v.size();
        arr = v;
        tree.resize(4*n+5);
        build(1,0,n-1);
    }
    void update(int ind,int val){update(1,0,n-1,ind,val);}
    int query(int l,int r,int x){return query(1,0,n-1,l,r,x+1);}
private:
    void build(int node,int start,int end){
        if(start==end)tree[node].insert(arr[start]);
        else {
            int mid = (start+end)/2;
            build(2*node,start,mid);
            build(2*node+1,mid+1,end);
            for(int i=start;i<=end;i++)tree[node].insert(arr[i]);
        }
    }
    void update(int node,int start,int end,int ind,int val){
        if(ind<start or ind>end)return;
        if(start==end){
            tree[node].erase(arr[ind]);
            tree[node].insert(val);
        }
        else {
            int mid = (start+end)/2;
            if(ind<=mid)update(2*node,start,mid,ind,val);
            else update(2*node+1,mid+1,end,ind,val);
            tree[node].erase(arr[ind]);
            tree[node].insert(val);
        }
    }
    int query(int node,int start,int end,int l,int r,int x){
        if(end<l or start>r)return INF;
        if(l<=start and end<=r){
            auto it = tree[node].lower_bound(x);
            if(it==tree[node].end())return INF;
            return *it;
        }
        else{
            int mid = (start+end)/2;
            int left = query(2*node,start,mid,l,r,x);
            int right = query(2*node+1,mid+1,end,l,r,x);
            return min(left,right);
        }
    }
};