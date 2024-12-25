vector<bool>chk(N+1,1);
vector<int>primes;
void sieve(){
    for(int i=3;i<=N;i+=2){
        if(chk[i]){
            for(int j=i*i;j<=N;j+=i+i)
                chk[j]=0;
        }
    }
    primes.pb(2);
    for(int i=3;i<=N;i+=2)if(chk[i])primes.pb(i);
}
int SegmentedSieve(int l,int r){
    if(l<3)l=2;
    vector<bool>is_prime(r-l+1,1);
    for(auto p : primes){
        int spm = (l/p) * p;
        if(spm < l)spm += p;
        if(spm==p)spm += p;
        for(int i=spm;i<=r;i+=p){
            is_prime[i-l] = 0;
        }
    }
    int cnt = 0;
    for(int i=l;i<=r;i++){
        if(is_prime[i-l]==1){
            cnt++;
        }
    }
    return cnt;
}