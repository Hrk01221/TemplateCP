void dnc(int k,int l,int r,int optl,int optr){
    if(l > r) return;
    int mid = (l+r) >> 1;
    int optm = optl;
    for(int i=optl;i<=min(mid,optr);i++){
        int ret = (i?dp[k-1][i-1]:0) +  cost(i,mid-1,a,b,x[mid]);
        if(ret < dp[k][mid]){
            dp[k][mid] = ret;
            optm = i;
        }
    }
    dnc(k,l,mid-1,optl,optm);  
    dnc(k,mid+1,r,optm,optr);
}
void solve(int tc){
    //init base case carefully
    dp[0][0] = 0;
    for(int i=1;i<=k;i++)dnc(i,1,n,1,n);
    cout << dp[k][n] << endl;
}