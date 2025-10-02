struct mint {
    int MOD = 1e9 + 7;
    int v;

    mint(long long _v = 0) {
        v = (_v % MOD + MOD) % MOD;
    }

    int val() const { return v; }

    mint operator+() const { return *this; }
    mint operator-() const { return mint(v ? MOD - v : 0); }

    mint& operator++() { if (++v == MOD) v = 0; return *this; }
    mint& operator--() { if (--v < 0) v += MOD; return *this; }

    mint& operator+=(const mint& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mint& operator-=(const mint& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mint& operator*=(const mint& o) { v = (v * o.v) % MOD; return *this; }//careful of overflow
    mint& operator/=(const mint& o) { return *this *= o.inv(); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }

    friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }
    friend bool operator<(const mint& a, const mint& b) { return a.v < b.v; }
    friend bool operator>(const mint& a, const mint& b) { return a.v > b.v; }
    friend bool operator<=(const mint& a, const mint& b) { return a.v <= b.v; }
    friend bool operator>=(const mint& a, const mint& b) { return a.v >= b.v; }

    mint binpow(long long n) const {
        mint x = *this, r = 1;
        while (n > 0) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const { return binpow(MOD - 2); } // Required mod prime

    friend ostream& operator<<(ostream &os, const mint &m) {
        return os << m.v;
    }
    friend istream& operator>>(istream &is, mint &m) {
        long long x; is >> x;
        m = mint(x);
        return is;
    }
};
