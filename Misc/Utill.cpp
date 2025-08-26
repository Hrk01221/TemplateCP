#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);//Fast IO
freopen("input.txt","r",stdin);//file IO
freopen("output.txt","w",stdout);
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int gen_random(int l, int r) {//gen random
    return uniform_int_distribution<int>(l, r)(rng);
}
shuffle(all(a),rng);//shuffle array randomly
__int128 x = 123456789012345678901234567890LL;
while(x) vec.push_back(x % 10 | 48), x /= 10;
reverse(vec.begin(), vec.end());//vec has all digits