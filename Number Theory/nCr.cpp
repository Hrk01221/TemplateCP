// DP
int C_pascal[MAXP][MAXP];
void build_pascal() {
    for (int n = 0; n < MAXP; n++) {
        C_pascal[n][0] = C_pascal[n][n] = 1;
        for (int r = 1; r < n; r++) {
            C_pascal[n][r] = C_pascal[n-1][r-1] + C_pascal[n-1][r];
        }
    }
}
// Inv MODULO + Factorial Precomputation
int fact[Max_N], invFact[Max_N];
void precompute_fact() {
    fact[0] = 1;
    for (int i = 1; i < Max_N; i++) fact[i] = fact[i-1] * i % MOD;
    invFact[Max_N-1] = binpow(fact[Max_N-1], MOD-2);
    for (int i = Max_N-2; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;
}
int nCr_mod(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}
// for small r
int nCr_multiplicative(int n, int r) {
    if (r < 0 || r > n) return 0;
    int ans = 1;
    for (int i = 1; i <= r; i++) {
        ans = ans * (n - i + 1) % MOD;
        ans = ans * binpow(i, MOD-2) % MOD;
    }
    return ans;
}
//Lucas Theorem (Huge n, small prime mod)
const int MOD = 7; // must be prime
int fact_lucas[MOD];
int invFact_lucas[MOD];
void precompute_lucas() {
    fact_lucas[0] = 1;
    for (int i = 1; i < MOD; i++) fact_lucas[i] = fact_lucas[i-1] * i % MOD;
    invFact_lucas[MOD-1] = binpow(fact_lucas[MOD-1], MOD-2, MOD);
    for (int i = MOD-2; i >= 0; i--)
        invFact_lucas[i] = invFact_lucas[i+1] * (i+1) % MOD;
}
int nCr_small_lucas(int n, int r) {
    if (r > n) return 0;
    return fact_lucas[n] * invFact_lucas[r] % MOD * invFact_lucas[n-r] % MOD;
}
int nCr_lucas(int n, int r) {
    if (r == 0) return 1;
    return nCr_lucas(n / MOD, r / MOD) * nCr_small_lucas(n % MOD, r % MOD) % MOD;
}

//Using Legendre's Formula - avoids intermediate overflow
int count_p(int n, int p) {
    int cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}
int nCr_exact(int n, int r) {
    if (r > n) return 0;
    int res = 1;
    for (int p = 2; p <= n; p++) {
        int exp = count_p(n, p) - count_p(r, p) - count_p(n-r, p);
        while (exp--) res *= p;
    }
    return res;
}