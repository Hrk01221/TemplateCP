#include<bits/stdc++.h>
using namespace std;

#define ll                 long long int
#define double             long double

const ll N = 1e6 + 1, mod1 = 1e9 + 7, mod2 = 1e9 + 9;
ll power1[N], power2[N], hsh1[N], hsh2[N], modInv1[N], modInv2[N];


ll gcdExtended(ll a, ll b, ll* x, ll* y)
{

	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}

	ll x1, y1;
	ll gcd = gcdExtended(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}


ll modInverse(ll A, ll M)
{
	ll x, y;
	ll g = gcdExtended(A, M, &x, &y);
	if (g != 1)
		cout << "Inverse doesn't exist";
	else {


		ll res = (x % M + M) % M;
		return res;
	}
}


void pre_hash()
{
	mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
	ll b1 = (500 + (rnd() % (mod1 - 500 * 2 + 1)));
	ll b2 = 0;
	do {
		b2 = (500 + (rnd() % (mod2 - 500 * 2 + 1)));
	} while (b1 == b2);
	power1[0] = 1;
	power2[0] = 1;
	for (ll i = 1; i < N; i++) {
		power1[i] = (power1[i - 1] * b1) % mod1;
		power2[i] = (power2[i - 1] * b2) % mod2;
		modInv1[i] = modInverse(power1[i], mod1);
		modInv2[i] = modInverse(power2[i], mod2);
	}

}

void rolling_hash(string &s)
{
	hsh1[0] = (s[0] - 'a' + 1);
	hsh2[0] = (s[0] - 'a' + 1);
	for (ll i = 1; i < s.size(); i++)
	{
		hsh1[i] = hsh1[i - 1] + (s[i] - 'a' + 1) * power1[i];
		hsh1[i] %= mod1;
		hsh2[i] = hsh2[i - 1] + (s[i] - 'a' + 1) * power2[i];
		hsh2[i] %= mod2;
	}
}


pair<ll, ll> get_double_hash(ll l, ll r)
{

	if (l == 0)
		return {hsh1[r], hsh2[r]};

	ll val1 = ((((hsh1[r] - hsh1[l - 1]) + mod1) % mod1) * modInv1[l]) % mod1;
	ll val2 = ((((hsh2[r] - hsh2[l - 1]) + mod2) % mod2) * modInv2[l]) % mod2;
	return {val1, val2};
}

pair<ll, ll> merge_hash(ll l1, ll r1, ll l2, ll r2)
{
	auto p1 = get_double_hash(l1, r1);
	auto p2 = get_double_hash(l2, r2);

	ll len = r1 - l1 + 1;

	pair<ll, ll>ans ;
	ans.first = {(p1.first + (p2.first*power1[len]) % mod1) % mod1};
	ans.second = {(p1.second + (p2.second*power2[len]) % mod2) % mod2};

	return ans;
}


int main()
{

	pre_hash();

	//string s = "abaasdasdasfasasfaba";
	string s;
	cin >> s;

	//hashcode for string s
	rolling_hash(s);
	ll n = s.size() - 1;
	cout << hsh1[n] << " " << hsh2[n];
	cout << "\n\n";


	// ## for finding substring existency in query

	/*	ll q;
		cin >> q;
		while (q--)
		{
			ll l, r;
			cin >> l >> r;
			auto hash = get_double_hash(l, r);
			cout << hash.first << " " << hash.second << " ";
		}*/


}