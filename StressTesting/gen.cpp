#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
inline ll gen_random(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}
 
 
// // Random Real Number Generator:
 
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
// inline double gen_random(double l, double r) {
//     return uniform_real_distribution<double>(l, r)(rng);
// }
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n = gen_random(1,100);
	cout << n << endl;
}