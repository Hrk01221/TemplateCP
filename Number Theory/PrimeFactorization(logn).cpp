vector<int>spf(N+1,1);
void sieve(){
    spf[0] = 0;
    for(int i=2;i<=N;i++){
        if(spf[i]==1){
            for(int j=i;j<=N;j+=i){
                if(spf[j]==1)
                    spf[j]=i;
            }
        }
    }
}
void getFactorization(int x,vector<int>&gg){
    while(x!=1){
        gg.pb(spf[x]);
        x = x/spf[x];
    }
}