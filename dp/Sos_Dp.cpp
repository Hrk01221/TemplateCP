#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define ff first
#define ss second
#define pb push_back
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define pii pair<int,int>
#define Fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int MOD = 1000000007;
const int INF = 1e18;
const int N = 2e5;
 
 
const int MLOG = 20;
const int MAXN = (1 << MLOG);
// Forward transform 1: add dp[sub] to all supersets
void forward1(vector<int> &dp) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = 0; i < MAXN; i++) {
            if (i & (1 << bit)) {
                dp[i] += dp[i ^ (1 << bit)];
            }
        }
    }
}
 
// Backward transform 1: undo forward1
void backward1(vector<int> &dp) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = MAXN - 1; i >= 0; i--) {
            if (i & (1 << bit)) {
                dp[i] -= dp[i ^ (1 << bit)];
            }
        }
    }
}
 
// Forward transform 2: add dp[sup] to all subsets
void forward2(vector<int> &dp) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = MAXN - 1; i >= 0; i--) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] += dp[i];
            }
        }
    }
}
 
// Backward transform 2: undo forward2
void backward2(vector<int> &dp) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = 0; i < MAXN; i++) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] -= dp[i];
            }
        }
    }
}
vector<int>f1(MAXN),f2(MAXN);
void solve(int tc){
    int n; cin >> n;
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
        f1[v[i]]++;
        f2[v[i]]++;
    }
    forward1(f1);
    forward2(f2);
    for(int i=0;i<n;i++){
        cout << f1[v[i]] << " " << f2[v[i]] << " " << n - f1[(MAXN - 1) ^ v[i]] << endl;
    }
}
int32_t main(){
    Fast
    int t=1;
    // cin >> t;
    for(int tc=1;tc<=t;tc++)
        solve(tc);
    return 0;
}
