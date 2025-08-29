// Signed area of polygon (CCW positive)
T areaPoly(const vector<pt>&p) {
    T area=0; int n=p.size();
    for(int i=0;i<n;i++) area+=cross(p[i],p[(i+1)%n]);
    return area/2.0;
}
// Point in arbitrary polygon (ray casting, O(n))
bool pointInPoly(const vector<pt>& poly, pt p) {
    bool inside=false; int n=poly.size();
    for(int i=0,j=n-1;i<n;j=i++) {
        if ((poly[i].y>p.y)!=(poly[j].y>p.y) &&
            p.x < (poly[j].x-poly[i].x)*(p.y-poly[i].y)/(poly[j].y-poly[i].y)+poly[i].x)
            inside=!inside;
    }
    return inside;
}
// Circle-line intersection: returns 0,1,2 points
vector<pt> circleLine(pt a, pt b, pt o, T r) {
    pt d=b-a; pt f=a-o;
    T A=dot(d,d), B=2*dot(f,d), C=dot(f,f)-r*r;
    T D=B*B-4*A*C;
    vector<pt>res;
    if(D<-eps) return res;
    D=max(D,(T)0);
    T t1=(-B-sqrt(D))/(2*A), t2=(-B+sqrt(D))/(2*A);
    if(0-eps<=t1 && t1<=1+eps) res.push_back(a+d*t1);
    if(0-eps<=t2 && t2<=1+eps && D>eps) res.push_back(a+d*t2);
    return res;
}

// Circle-circle intersection: returns 0,1,2 points
vector<pt> circleCircle(pt o1, T r1, pt o2, T r2) {
    T d=dist(o1,o2);
    if(d>r1+r2+eps||d<fabs(r1-r2)-eps) return {};
    T x=(d*d-r2*r2+r1*r1)/(2*d);
    T y2=r1*r1-x*x;
    y2=max((T)0,y2);
    T y=sqrt(y2);
    pt v=(o2-o1)/d;
    pt p=o1+v*x, perp={-v.y,v.x};
    if(y==0) return {p};
    return {p+perp*y, p-perp*y};
}
// Convex polygon intersection (O(n+m)) using half-plane method
vector<pt> convexInter(vector<pt>A, vector<pt>B) {
    // simple version: clip A by all edges of B
    auto clip=[&](vector<pt>P, pt a, pt b){
        vector<pt>Q; int n=P.size();
        for(int i=0;i<n;i++){
            pt c=P[i], d=P[(i+1)%n];
            T o1=orient(a,b,c), o2=orient(a,b,d);
            if(o1>=-eps) Q.push_back(c);
            if(o1*o2<0) Q.push_back(lineInter(a,b,c,d));
        }
        return Q;
    };
    for(int i=0,n=B.size();i<n && !A.empty();i++)
        A=clip(A,B[i],B[(i+1)%n]);
    return A;
}
// Convex polygon diameter (max distance, rotating calipers)
T convexDiameter(vector<pt>&p) {
    int n=p.size(); if(n==1) return 0;
    int j=1; T best=0;
    for(int i=0;i<n;i++) {
        while(fabs(cross(p[(i+1)%n]-p[i], p[(j+1)%n]-p[i])) >
              fabs(cross(p[(i+1)%n]-p[i], p[j]-p[i])))
            j=(j+1)%n;
        best=max(best,dist(p[i],p[j]));
    }
    return best;
}