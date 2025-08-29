vector<pt> ConvexHull(vector<pt>&pts){
    vector<pt>points = pts,hull;
    sort(all(points));
    points.erase(unique(all(points)),points.end());
    int n = points.size();
    if(points.size()<=2){
        return points;
    }
    for(int i=0;i<n;i++){
        while(hull.size()>1&&
            orient(hull[hull.size()-2],hull.back(),points[i])<=0){
            //<=0 to remove co-linear edges
            hull.pop_back();
        }
        hull.pb(points[i]);
    }
    auto lhs = hull.size();
    for(int i=n-2;i>=0;i--){
        while(hull.size()>lhs &&
            orient(hull[hull.size() - 2], hull.back(), points[i])<=0){
            //<=0 to remove co-linear edges
            hull.pop_back();
        }
        hull.pb(points[i]);
    }
    hull.pop_back();
    return hull;
}