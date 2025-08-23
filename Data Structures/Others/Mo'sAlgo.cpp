int Mx = 100005;
struct Query{int l,r,ind;};
bool cmp(Query &a,Query &b){
    int blocks_size = sqrt(Mx);
    if(a.l/blocks_size!=b.l/blocks_size)
        return a.l/blocks_size < b.l/blocks_size;
    return a.r < b.r;
}
void add(int ind,int &d){}
void remove(int ind,int &d){}
vector<Query>qu(q);
for(int i=0;i<q;i++){
    int l,r; cin >> l >> r;
    qu[i] = {l-1,r-1,i};
}
sort(all(qu),cmp);
vector<int>result(q);
int curr_l = 0 , curr_r = -1 , d = 0;
for(int i=0;i<q;i++){
    int l = qu[i].l;
    int r = qu[i].r;
    while(curr_r<r)add(v[++curr_r],d);
    while(curr_r>r)remove(v[curr_r--],d);
    while(curr_l<l)remove(v[curr_l++],d);
    while(curr_l>l)add(v[--curr_l],d);
    result[qu[i].ind] = d;
}