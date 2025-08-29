int closestPair(vector<pt>&points) {
    int n = points.size();
    sort(points.begin(), points.end(), cmp);
    set<pair<int,int>> st;
    long long mn = INF;
    int j = 0;
    for (int i = 0; i < n; i++) {
        long long d = (mn == INF ? INF : (long long)ceil(sqrt(mn)));
        while (points[i].x - points[j].x >= d) {
            st.erase({points[j].y, points[j].x});
            j++;
        }
        auto it1 = st.lower_bound({points[i].y - d, -INF});
        auto it2 = st.upper_bound({points[i].y + d, INF});
        for (auto it = it1; it != it2; ++it) {
            long long dx = points[i].x - it->second;
            long long dy = points[i].y - it->first;
            mn = min(mn, dx*dx + dy*dy);
        }
        st.insert({points[i].y, points[i].x});
    }
    return mn; 
}