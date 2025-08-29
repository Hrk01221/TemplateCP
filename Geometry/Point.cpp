const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double) - 1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
typedef double T;
struct pt {
    T x, y;
    pt() {x = y = 0;}
    pt(T x, T y) : x(x) , y(y) {}
    pt(const pt &p) : x(p.x) , y(p.y) {}
    pt operator+(pt p) {return pt(x + p.x, y + p.y);}
    pt operator-(pt p) {return pt(x - p.x, y - p.y);}
    pt operator*(T d) {return pt(x * d, y * d);}
    pt operator/(T d) {return pt(x / d, y / d);}
    bool operator==(pt a) {return sign(a.x - x) == 0 && sign(a.y - y) == 0;}
    bool operator!=(pt a) {return !(*this == a);}
    bool operator < (pt a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (pt a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    T sq() {return x * x + y * y;}
    T abs() {return sqrt(sq());}
    T arg() {return atan2(y, x);}
    pt perp() {return { -y, x};}
};
inline T dot(pt a, pt b) {return a.x * b.x + a.y * b.y;}
inline bool isPerp(pt v, pt w) {return dot(v, w) == 0;}
inline T cross(pt a, pt b) {return a.x * b.y - a.y * b.x;}//signed area
inline T dist2(pt a, pt b) {return dot(a - b, a - b);}
inline T dist(pt a, pt b) {return sqrt(dist2(a, b));}
inline T orient(pt a, pt b, pt c) {return cross(b - a, c - a);}//in which side c appears of ab
inline T angle(pt v, pt w) {
    T costheta = dot(v, w) / v.abs() / w.abs();
    return acos(max(-1.0, min(1.0, costheta)));
}
bool half(pt p) {return p.y > 0 || (p.y == 0 && p.x < 0);}
void polar_sort(vector<pt> &v, pt o) {
// sort points in counterclockwise with respect to point o
    sort(v.begin(), v.end(), [&](pt a,pt b) {
        return make_tuple(half(a - o), 0.0, (a - o).sq()) < 
               make_tuple(half(b - o), cross(a - o, b - o), (b - o).sq());
    });
}