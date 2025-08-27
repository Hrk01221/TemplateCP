int gcd(int a, int b) {
    while (b) tie(a, b) = make_pair(b, a % b);
    return a;
}

int mulmod(int a, int b, int mod) {
    int res = 0;
    a %= mod;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

int powmod(int a, int b, int mod) {
    int res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return res;
}
//Primality Test n <= 1e18
bool MIllerRabin(int n) {
    if (n < 2) return false;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    int d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, s++;
    for (int a : {2, 3, 5, 7, 11}) {
        if (a >= n) continue;
        int x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool witness = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                witness = false;
                break;
            }
        }
        if (witness) return false;
    }
    return true;
}
//Factorization
int pollard(int n) { // O(n^1/4)
    if (n % 2 == 0) return 2;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int x = rng() % (n - 1) + 1;
        int y = x, c = rng() % (n - 1) + 1, d = 1;
        while (d == 1) {
            x = (mulmod(x, x, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            d = gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

void factor(int n, map<int, int> &f) {
    if (n == 1) return;
    if (MIllerRabin(n)) {
        f[n]++;
        return;
    }
    int d = pollard(n);
    factor(d, f);
    factor(n / d, f);
}