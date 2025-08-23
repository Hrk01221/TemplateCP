const int MAXN=1001;
struct BIT2D{//1 based
    int tree[4][MAXN][MAXN];
    BIT2D(){memset(tree,0,sizeof(tree));}
    void update(int p,int q,int v){
        if(p<=0||q<=0||p>=MAXN||q>=MAXN) return;
        int i=p,c=p-1,d=q-1;
        while(i<MAXN){
            int j=q;
            while(j<MAXN){
                tree[0][i][j]+=v; tree[1][i][j]+=v*d;
                tree[2][i][j]+=v*c; tree[3][i][j]+=v*c*d;
                j+=j&-j;
            }
            i+=i&-i;
        }
    }
    int query(int p,int q){
        int i,j,x=0,y=0,z=0,c,d,res;
        i=p;
        while(i!=0){
            j=q; c=d=0;
            while(j!=0){
                c+=tree[0][i][j]; d+=tree[1][i][j];
                y+=tree[2][i][j]; z+=tree[3][i][j];
                j^=j&-j;
            }
            i^=i&-i;
            x+=c*q-d;
        }
        res=x*p - y*q + z;
        return res;
    }
    void update(int i,int j,int k,int l,int v){
        update(i,j,v); update(k+1,j,-v);
        update(k+1,l+1,v); update(i,l+1,-v);
    }
    int query(int i,int j,int k,int l){
        if(i>k||j>l) return 0;
        int res=query(k,l)-query(i-1,l);
        res+=query(i-1,j-1)-query(k,j-1);
        return res;
    }
};
//might not run in compiler