const int MOD[2] = {998244353, 1000000007};
int BASE[2] = {0, 0};
int POW[2][MX];
int IPOW[2][MX];
int power(int a, int p, int m) {
  int ans = 1;
  a %= m;
  while (p) {
    if (p & 1) ans = (ans*a) % m;
    p >>= 1;
    a = (a*a) % m;
  }
  return ans;
}
void hash_pre() {//Call this idiot
  int b1, b2, i, j, inv;
  mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
  b1 = (500 + (rnd() % (MOD[0]-500*2+1)));
  b2 = 0;
  do {
    b2 = (500 + (rnd() % (MOD[1]-500*2+1)));
  } while (b1 == b2);
  BASE[0] = b1;
  BASE[1] = b2;
  for (i = 0; i < 2; ++i) {
    int *pw = POW[i], *ipw = IPOW[i], x = BASE[i], m = MOD[i];
    pw[0] = 1;
    ipw[0] = 1;
    inv = power(x, m-2, m);
    for (j = 1; j < MX; ++j) {
      pw[j] = (pw[j-1] * x) % m;
      ipw[j] = (ipw[j-1] * inv) % m;
    }
  }
}
template<typename T>
struct DoubleHash {
  int n;
  T s;
  vector<pair<int,int>> h;
  DoubleHash() {}
  DoubleHash(T s) : s(s) {//0 based
    n = s.size();
    h.resize(n+1);
	int *pw0 = POW[0], m0 = MOD[0];
    int *pw1 = POW[1], m1 = MOD[1];
    int i = 0;
    h[i] = {0, 0};    
    for (i = 1; i <= n; ++i) {
      h[i] = {
        (h[i-1].first + pw0[s[i-1]]) % m0,
        (h[i-1].second + pw1[s[i-1]]) % m1,
      };
    }
  }
  pair<int,int> get_hash(int l, int r) {//0 based
    assert((0 <= l) && (l <= r) && (r < n));
    ++l; ++r;
    int *ipw0 = IPOW[0], m0 = MOD[0];
    int *ipw1 = IPOW[1], m1 = MOD[1];
    return {
      (h[r].first - h[l-1].first + m0) % m0,
      (h[r].second - h[l-1].second + m1) % m1,
    };
  }
  pair<int,int> get_hash() {
    return get_hash(0, n-1);
  }
};