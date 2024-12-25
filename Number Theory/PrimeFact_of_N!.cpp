void Nfact_PF(int n){
    //Sieve till n and generate all primes <= n
    for(auto it : primes){
        int c = it , cnt = 0;
        if(c > n)break;
        while(c<=n){
            cnt += n / c;
            c *= it;
        }
        cout << it << " " << cnt << endl;
    }
}