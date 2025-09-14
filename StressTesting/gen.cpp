#include <bits/stdc++.h>
using namespace std;
#define int long long
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int gen_random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// // Random Real Number Generator:
 
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
// inline double gen_random(double l, double r) {
//     return uniform_real_distribution<double>(l, r)(rng);
// }

// ---------------- PRINTING GENERATORS ---------------- //

// Print array of size n with values in [L, R]
void print_array(int n, int L = -1e9, int R = 1e9) {
    for (int i = 0; i < n; i++) {
        cout << gen_random(L, R) << " ";
    }
    cout << "\n";
}

// Print tree with n nodes
void print_tree(int n) {
    for (int i = 2; i <= n; i++) {
        int parent = gen_random(1, i - 1);
        cout << parent << " " << i << "\n";
    }
}

// Print simple graph with n nodes and m edges
void print_graph(int n, int m) {
    set<pair<int,int>> edges;
    while ((int)edges.size() < m) {
        int u = gen_random(1, n);
        int v = gen_random(1, n);
        if (u != v) {
            if (u > v) swap(u, v);
            edges.insert({u, v});
        }
    }
    for (auto [u, v] : edges) {
        cout << u << " " << v << "\n";
    }
}

// Print random permutation of size n
void print_permutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    for (int x : p) cout << x << " ";
    cout << "\n";
}

// Print q random queries (l, r) on array of size n
void print_queries(int q, int n) {
    for (int i = 0; i < q; i++) {
        int l = gen_random(1, n);
        int r = gen_random(1, n);
        if (l > r) swap(l, r);
        cout << l << " " << r << "\n";
    }
}

// ---------------- EXAMPLE USAGE ---------------- //

void generate_testcase() {
    int n = gen_random(2, 10);  
    cout << n << "\n";

    // Array
    print_array(n, -10, 10);

    // Tree
    print_tree(n);

    // Queries
    int q = gen_random(1, 5);
    cout << q << "\n";
    print_queries(q, n);

    // Permutation
    print_permutation(n);
}

int32_t main() {
    FAST
    generate_testcase();
}
