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
/*
	to check prime
		if(n%2==0)return n==2;
		else if(n&1 and chk[i])return 1;
		else return 0;
*/