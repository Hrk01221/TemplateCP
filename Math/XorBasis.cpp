const int B = 31,N = 1e5+1;
bitset<N>comb[B],bit;
struct Basis {
  int a[B],sz;
  Basis() {
    sz = 0;memset(a, 0, sizeof a);
  }
  void insert(int x,int id){
  	bit.reset();
  	bit[id]=1;
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (a[i]) {x ^= a[i];bit ^= comb[i];}
        else {
          sz++;a[i] = x;
          comb[i] = bit;
          break;
        }
      }
    }
  }
  void make(int s) {
    bit.reset();
    for (int i = B - 1; i >= 0; i--)
        if (a[i] and !(s >> i & 1)) {
            s ^= a[i];
            bit ^= comb[i];
        }
  }
  bool can(int x) {
    for(int i = B - 1; i >= 0; i--) 
      x = min(x, x ^ a[i]);
    return x == 0;
  }
  int max_xor(int ans = 0) {
    for(int i = B - 1; i >= 0; i--)
      ans = max(ans, ans ^ a[i]);
    return ans;
  }
};