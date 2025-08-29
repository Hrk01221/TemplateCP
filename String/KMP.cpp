//pi[i] - >  maximum length of suffix which is also a prefix in substring s[0....i]
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
vector<int> search(string &pat, string &txt) {
    int n = txt.length(), m = pat.length();
    vector<int> lps = prefix_function(pat), res;
    int i = 0, j = 0;
    while (i < n) {
        if (txt[i] == pat[j]) {
            i++; j++;
            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return res;
}