// len -> largest string length of the corresponding endpos-equivalent class
// link -> longest suffix that is another endpos-equivalent class.
// minlen(v) -> smallest string of node v = len(link(v)) + 1
// terminal nodes -> store the suffixes
/*
    must remember root = 0
    firstpos -> 1 indexed end position of the first occurrence of the largest string of that node
    for each state v all substring of t[t[v].link].len + 1  to t[v].len appears
*/
struct SuffixAutomaton {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    vector<int> terminal;
    vector<int> cnt , way , tot; // if !needed Remove from construtor
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n) {
        t.resize(2 * n); terminal.resize(2 * n, 0);
        sz = 1; last = 0;
        cnt.resize(2 * n, -1);//remove if !need
        way.resize(2 * n, -1);//remove if !need
        tot.resize(2 * n, -1);//remove if !need
        g.resize(2 * n);
        t[0].len = 0; t[0].link = -1; t[0].firstpos = 0;
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree() { // suffix link tree
        for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
    }
    void build(string &s) {
        for (auto x : s) {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    int cnt_occ(int i) { //number of times i-th node occurs in the string
        if (cnt[i] != -1) return cnt[i];
        int ret = terminal[i];
        for (auto &x : g[i]) ret += cnt_occ(x);
        return cnt[i] = ret;
    }
    int cnt_ways(int i) { // how many substr occurs in node i
        if (way[i] != -1)return way[i];
        int ret = 0;
        for (auto [ch, ind] : t[i].nxt) {
            ret += cnt_ways(ind);
            ret += cnt_occ(ind);
        }
        return way[i] = ret;
    }
    int cnt_tot(int i) { //# of distinct sub-string staring at the node i
        if (tot[i] != -1)return tot[i];
        tot[i] = 0;
        for (auto [ch, ind] : t[i].nxt) {
            tot[i] += 1 + cnt_tot(ind);
        }
        return  tot[i];
    }
};
int cnt_distinct_substring(string &s) {
    SuffixAutomaton sa(s.size());
    sa.build(s);
    int ans = 0;
    for (int i = 1; i < sa.sz; i++)
        ans += sa.t[i].len - sa.t[sa.t[i].link].len;
    return ans;
}
string kth_substr(string &s , int k) {
    SuffixAutomaton sa(s.size());
    sa.build(s); sa.cnt_occ(0); sa.cnt_ways(0);
    int node = 0; string ans = "";
    while (k > 0) {
        for (auto [ch, ind] : sa.t[node].nxt) {
            int cnt = sa.cnt[ind] + sa.way[ind];
            if (k > cnt)k -= cnt;
            else {
                ans += ch;
                k -= sa.cnt[ind];
                if (k <= 0)return ans;
                node = ind;
                break;
            }
        }
    }
    return ans;
}
string kth_distinct_substr(string &s , int k) {
    SuffixAutomaton sa(s.size());
    sa.build(s); sa.cnt_tot(0);
    if (k > sa.tot[0])return "";
    int node = 0; string ans = "";
    while (k > 0) {
        for (auto [ch , ind] : sa.t[node].nxt) {
            int cnt = 1 + sa.tot[ind];
            if (k > cnt)k -= cnt;
            else {
                ans += ch;
                k--;
                if (k == 0)return ans;
                node = ind;
                break;
            }
        }
    }
}
//returns any index where a[i...j] = b[k...l]
tuple<int, int, int, int> longest_common_substring(string &a, string &b) {
    SuffixAutomaton sa(a.size());
    sa.build(a);
    int node = 0, len = 0 , ed = -1 , best = 0;
    for (int i = 0; i < b.size(); i++) {
        while (node && !sa.t[node].nxt.count(b[i])) {
            node = sa.t[node].link;
            len = sa.t[node].len;
        }
        if (sa.t[node].nxt.count(b[i])) {
            len++;
            node = sa.t[node].nxt[b[i]];
        }
        if (len > best) {
            best = len;
            ed = i;
        }
    }
    if (best == 0)return {0, 0, 0, 0};
    else {
        int i = 0;
        string lcs = b.substr(ed - best + 1, best);
        for (auto it : lcs)i = sa.t[i].nxt[it];
        int ed2 = sa.t[i].firstpos - 1;
        return {ed2 - best + 1, ed2, ed - best + 1, ed};
    }
}
int LCS_ManyStrings(vector<string> &v) {
    int n = v.size();
    SuffixAutomaton sa(v[0].size());
    sa.build(v[0]);

    vector<int>ord;
    for (int i = 0; i < sa.sz; i++)ord.push_back(i);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return sa.t[a].len > sa.t[b].len;
    });

    vector<int>par(sa.sz, 1e9);
    for (int i = 1; i < n; i++) {
        vector<int>tmp(sa.sz);
        int node = 0 , l = 0;
        for (auto it : v[i]) {
            while (node && !sa.t[node].nxt.count(it)) {
                node = sa.t[node].link;
                l = sa.t[node].len;
            }
            if (sa.t[node].nxt.count(it)) {
                l++;
                node = sa.t[node].nxt[it];
            }
            tmp[node] = max(tmp[node] , l);
        }
        //this part of propagation is needed
        //to propagate all the ans to shoter substr
        for (auto nde : ord) {
            int parent = sa.t[nde].link;
            if (parent != -1) {
                tmp[parent] = max(tmp[parent] ,
                                  min(tmp[nde], sa.t[parent].len));
            }
        }
        for (int i = 0; i < sa.sz; i++) {
            par[i] = min(par[i] , tmp[i]);
        }
    }
    return *max_element(par.begin(), par.end());
}
