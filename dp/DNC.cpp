long long cost(int i, int j, vector<long long>&pref) {
    if (j < i)return INF;
    long long sum = pref[j] - pref[i - 1];
    sum = (sum * (sum + 1)) / 2;
    return sum;
}
void compute(int groupNo , int L , int R, int optL , int optR , vector<vector<long long>>&dp , vector<long long>&pref) {
    if (L > R)return;
    int mid = (L + R) >> 1;
    int id = groupNo;
    dp[id][mid] = INF;
    int optNow = optL;
    for (int j = optL; j <= optR && j < mid; j++) {
        long long ret = dp[id - 1][j] + cost(j + 1 , mid , pref);
        if (ret < dp[id][mid]) {
            dp[id][mid] = ret;
            optNow = j;
        }
    }
    cout << mid << " " << dp[id][mid] << endl;
    compute(groupNo , L , mid - 1 , optL , optNow , dp , pref);
    compute(groupNo , mid + 1 , R , optNow , optR , dp , pref);
}
long long minPartitionScore(vector<int>&nums, int k) {
    int n = nums.size();
    vector<long long>v;
    v.push_back(0);
    for (auto it : nums) v.push_back(it);
    for (int i = 1; i <= n; i++)v[i] += v[i - 1];
    vector<vector<long long>>dp(k + 1 , vector<long long>(n + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++)compute(i , 1 , n , 0 , n - 1 , dp , v);
    return dp[k][n];
}
