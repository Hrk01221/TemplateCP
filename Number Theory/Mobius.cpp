vector<int>mobb(N);
void Mobius() {//O(NLogN)
    mobb[1] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            if (j != i)mobb[j] -= mobb[i];
        }
    }
}
vector<int> mobb(N+1, 1), primes;
vector<bool> isComp(N+1, false);
void mobius_sieve() {//O(N)
    mobb[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!isComp[i]) {
            primes.push_back(i);
            mobb[i] = -1;
        }
        for (int p : primes) {
            if (1LL * i * p > N) break;
            isComp[i * p] = true;
            if (i % p == 0) {
                mobb[i * p] = 0;
                break;
            } else {
                mobb[i * p] = -mobb[i];
            }
        }
    }
}