//find primes till Max_N
const int Max_N = 1e6 + 10;
vector<int>primes , chk(Max_N,1);
void sieve(){
    for(int i=3;i<Max_N;i+=2){
        if(chk[i]){
           	for(int j=i*i;j<Max_N;j+=i+i){
                chk[j] = 0;
            }
        }
    }
    chk[2]=1;
    primes.pb(2);
    for(int i=3;i<Max_N;i+=2){
        if(chk[i])primes.pb(i);
    }
}
//Check Prime
vector<bool> is_prime(N+1, true);
void sieve(){
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i){

                is_prime[j] = false;
            }
        }
    }
}
//Smallest Prime Factor log(n)
vector<int>spf(N+1,-1);
void sieve(){
    for (int i = 2; i <= N; i++) {
        if (spf[i]==-1) {
            spf[i] = i;
            for (int j = i+i; j <= N; j += i){
                if(spf[j]==-1)spf[j] = i;
            }
        }
    }
}
vector<int>PrimeFactors(int n){
    vector<int>PF;
    while(n > 1){
        PF.pb(spf[n]);
        n/=spf[n];
    }
    return PF;
}
