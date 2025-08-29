// Line intersection (assuming not parallel)
pt lineInter(pt a, pt b, pt c, pt d) {
    T cross1 = cross(b-a, d-c);
    assert(fabs(cross1) > eps);
    return a + (b-a) * (cross(c-a, d-c) / cross1);
}
// Check if point q lies on segment pr
bool onSeg(pt p, pt q, pt r) {
    return sign(cross(q-p, r-p))==0 &&
           min(p.x,r.x)-eps <= q.x && q.x <= max(p.x,r.x)+eps &&
           min(p.y,r.y)-eps <= q.y && q.y <= max(p.y,r.y)+eps;
}
// Segment-segment intersection
bool segInter(pt p1, pt q1, pt p2, pt q2) {
    T o1 = orient(p1,q1,p2);
    T o2 = orient(p1,q1,q2);
    T o3 = orient(p2,q2,p1);
    T o4 = orient(p2,q2,q1);
    if (o1*o2<0 && o3*o4<0) return true;
    if (o1==0 && onSeg(p1,p2,q1)) return true;
    if (o2==0 && onSeg(p1,q2,q1)) return true;
    if (o3==0 && onSeg(p2,p1,q2)) return true;
    if (o4==0 && onSeg(p2,q1,q2)) return true;
    return false;
}
// Distance from point p to line ab
T distPointLine(pt p, pt a, pt b) {
    return fabs(cross(b-a, p-a))/dist(a,b);
}
// Distance from point p to segment ab
T distPointSeg(pt p, pt a, pt b) {
    if (dot(b-a, p-a) < 0) return dist(p,a);
    if (dot(a-b, p-b) < 0) return dist(p,b);
    return distPointLine(p,a,b);
}