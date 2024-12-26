const int Max_N = 1e6 + 10;
vector<int>factorial(Max_N),inv(Max_N);
void Calc_factorial(){
    factorial[0] = 1;
    for(int i=1;i<Max_N;i++){
        factorial[i] = (factorial[i-1] * i) % MOD;
    }
}
void inverseModulo(){
    inv[1] = 1;inv[0] = 1;
    for(int i=2;i<Max_N;i++){
        inv[i] = inv[MOD%i] * (MOD - MOD/i) % MOD;
    }
}
int nCr(int n,int r){
    return (factorial[n] * inv[factorial[r]] % MOD * inv[factorial[n-r]] % MOD);
}
void pre(){
    Calc_factorial();
    inverseModulo();
}
//_______________________________________________//
int dp[31][31];
int fun(int n,int r){
    if(r > n)return 0;
    if(r == 0 or r == n)return 1;
    int &ret = dp[n][r];
    if(ret != -1) return ret;
    ret = fun(n-1,r-1) + fun(n-1,r);
    return ret;
}
void prec(){
	for(int i=0;i<31;i++)
        for(int j=0;j<31;j++)
            dp[i][j] = -1;
    for(int i=0;i<=30;i++){
        for(int j=0;j<=30;j++)
            fun(i,j);
    }
}