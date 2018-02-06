typedef long long ll;
typedef double lf;
typedef complex<lf> pt, vec;
istream &operator >> (istream &in, pt &p) {
    lf x, y; in >> x >> y;
    p = pt(x, y);
    return in;
}
const lf pi = acos(-1);
const lf eps = 1e-9;

#define equals(a,b) (fabs((a)-(b)) < eps)
#define x(a) real(a)
#define y(a) imag(a)
#define cross(a, b) imag(conj((a))*(b))
#define dot(a, b) real(conj((a))*(b))

int cmp (lf a, lf b) { return (a + eps < b ? -1 :(b + eps < a ? 1 : 0)); }
lf dist (pt a, pt b) { return abs(a - b); }
lf distSq (pt a, pt b) { return norm(a - b); }
pt midPoint (pt a, pt b) { return (a + b) / 2.0; }
pt linePointAt (pt a, pt b, lf x) { return a + (b - a) * x; }
pt rotate (pt a, lf ang) { return a * exp(ang * pt(0, 1)); }
pt rotateToB (pt a, pt b, lf ang) { return rotate(a - b, ang) + b; }
pt rotate90CCW (pt a) { return a * pt(0, 1); }
pt rotate90CW (pt a) { return a * pt(0, -1); }
lf angle (pt a, pt b) { return asin(cross(a, b) / norm(a) / norm(b)); }
lf angle (pt a, pt b) { return atan2(cross(a, b), dot(a, b)); }
lf trianglearea (pt a, pt b, pt C) {
    return abs(cross(b - a, C - a)) / 2.0;
}
pt unit (pt a) { return a / abs(a); }
void perpBisector (pt a, pt b, pt &C, pt &D) {
    C = midPoint(a, b);
    D = C + rotate90CW(a - b);
}
pt bisector (pt a, pt b) {
    if (cross(a, b) == 0) return rotate90CW(b);
    return midPoint(unit(a), unit(b));
}
void trianglebisector (pt a, pt b, pt C, pt &P1, pt &P2) {
    P1 = a;
    P2 = a + midPoint(unit(b - a), unit(C - a));
}
bool pointInTriangle (pt a, pt b, pt c, pt p) {
    return cmp(abs(cross(b-a,c-a)),
        abs(cross(a-p,b-p)) +
        abs(cross(b-p,c-p)) +
        abs(cross(c-p,a-p))) == 0;
}
struct circle { pt p; lf r; };
struct line { pt p; pt q; };
typedef line segment;

int COUNTER_CLOCKWISE = 1;
int CLOCKWISE = -1;
int ONLINE_BACK = 2;
int ONLINE_FRONT = -2;
int ON_SEGMENT = 0;

int ccw (pt p, pt p1, pt p2) {
    pt a = p1 - p;
    pt b = p2 - p;
    if (cross(a, b) > eps) return COUNTER_CLOCKWISE;
    if (cross(a, b) < -eps) return CLOCKWISE;
    if (dot(a, b) < -eps) return ONLINE_BACK;
    if (norm(a) < norm(b)) return ONLINE_FRONT;
    return ON_SEGMENT;
}
/// tested at http://codeforces.com/group/3qadGzUdR4/contest/101704/problem/V
pair<pt, pt> circlesIntersection (pt &c1, lf r1, pt &c2, lf r2) {
    lf d2 = dot((c1 - c2), (c1 - c2));
    lf d = sqrt(d2);
    if (d < abs(r1 - r2)) return {};
    if (d > r1 + r2) return {};
    pt u = 0.5 * (c1 + c2) + ((r2 * r2 - r1 * r1) / (2 * d2)) * (c1 - c2);
    double a = sqrt((r1 + r2 + d) * (r1 - r2 + d) *
                    (r1 + r2 - d) * (-r1 + r2 + d));
    pt v = a / (2 * d2) * pt(y(c1) - y(c2), -x(c1) + x(c2));
    return make_pair(u + v, u - v);
}
pair<pt, pt> circlesIntersection (circle &c1, circle &c2) {
    return circlesIntersection(c1.p, c1.r, c2.p, c2.r);
}
circle get_circle (pt a, pt b, pt c) {
    pt x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
    pt t = (y - x) / (conj(x) * y - x * conj(y)) + a;
    return {t, abs(a - t)};
}
bool intersectLL (line l, line m) {
    return abs(cross(l.q - l.p, m.q - m.p)) > eps || // non-parallel
        abs(cross(l.q - l.p, m.p - l.p)) < eps; // same line
}
bool intersectLS (line l, segment s) {
    return cross(l.q - l.p, s.p - l.p) * // s[0] is left of l
        cross(l.q - l.p, s.q - l.p) < eps; // s[1] is right of l
}
bool intersectLP (line l, pt p) {
    return abs(cross(l.q - p, l.p - p)) < eps;
}
bool intersectSS (segment s, segment t) {
    return ccw(s.p, s.q, t.p) * ccw(s.p, s.q, t.q) <= 0 &&
           ccw(t.p, t.q, s.p) * ccw(t.p, t.q, s.q) <= 0;
}
bool intersectSP (segment s, pt p) {
    return abs(s.p - p) + abs(s.q - p) - abs(s.q - s.p) < eps;
    // triangle inequality
    return min(real(s.p), real(s.q)) <= real(p) &&
               real(p) <= max(real(s.p), real(s.q)) &&
               min(imag(s.p), imag(s.q)) <= imag(p) &&
               imag(p) <= max(imag(s.p), imag(s.q)) &&
               cross(s.p - p, s.q - p) == 0;
}
bool helper (pt a, pt b, pt p) {
    return cmp ( dot ( a-p, b-p ), 0 ) <= 0;
}
lf distToSegment (pt a, pt b, pt p) {
    if (a == b) return dist(a, p);
    if (dot(b - a, p - b) > 0) return dist(b, p);
    if (dot(a - b, p - a) > 0) return dist(a, p);
    return abs(cross(a - p, b - p) / (b - a));
}
bool segTouch (pt a, pt b, pt c, pt d) {
    if (cmp(cross(b - a, d - c), 0) == 0) {
        return cmp(distToSegment(a, b, c), 0) == 0 ||
               cmp(distToSegment(a, b, d), 0) == 0 ||
               cmp(distToSegment(c, d, a), 0) == 0 ||
               cmp(distToSegment(c, d, b), 0) == 0;
    }
    return sign(cross(b - a, c - a)) * sign(cross(b - a, d - a)) != 1 &&
           sign(cross(d - c, a - c)) * sign(cross(d - c, b - c)) != 1;
}
seg segIntersection (pt a, pt b, pt c, pt d) {
    if (cmp(cross(b - a, d - c), 0) == 0) {
        vector<pt> cur;
        if (helper(a, b, c)) cur.push_back(c);
        if (helper(a, b, d)) cur.push_back(d);
        if (helper(c, d, a)) cur.push_back(a);
        if (helper(c, d, b)) cur.push_back(b);
        vector<pt> ncur;
        for (int i = 0; i < cur.size(); i++) {
            bool ok = true;
            for (int j = 0; j < ncur.size(); j++)
                ok &= ncur[j] != cur[i];
            if (ok)
                ncur.push_back(cur[i]);
        }
        if (ncur.size() == 1) ncur.push_back(ncur[0]);
        assert(ncur.size() == 2);
        return seg(ncur[0], ncur[1]);
    }
    seg ret;
    ret.first = lines_intersection(a, b, c, d);
    ret.second = ret.first;
    return ret;
}
pt linesIntersection (pt a, pt b, pt c, pt d) {
    lf s = cross(c - a, d - c) / cross(b - a, d - c);
    return a + (b - a) * s;
}
pt linesIntersection (line l1, line l2) {
    return linesIntersection(l1.p, l1.q, l2.p, l2.q);
}
pt projection (line l, pt p) {
    lf t = dot(p - l.p, l.p - l.q) / norm(l.p - l.q);
    return l.p + t * (l.p - l.q);
}
pt reflection (line l, pt p) {
    return p + 2.0 * (projection(l, p) - p);
}
// projection of p onto p1->p2
pt projection (pt p1, pt p2, pt p) {
    pt a = p2 - p1;
    pt b = p - p1;
    pt r = a * dot(a, b) / norm(a);
    return p1 + r;
}
//projection of vector b onto a
vec projection (vec a, vec b) {
    return a * dot(a, b) / norm(a);
}
//reflection of p onto p1->p2
pt reflection (pt p1, pt p2, pt p) {
    return 2.0 * projection(p1, p2, p) - p;
}
//reflection of b onto a
vec reflection (vec a, vec b) {
    return 2.0 * projection(a, b) - b;
}
lf distanceLP (line l, pt p) {
    return abs(p - projection(l, p));
}
lf distanceLL (line l, line m) {
    return intersectLL(l, m) ? 0 : distanceLP(l, m.p);
}
lf distanceLS (line l, line s) {
    if (intersectLS(l, s)) return 0;
    return min(distanceLP(l, s.p), distanceLP(l, s.q));
}
lf distanceSP (segment s, pt p) {
    pt r = projection(s, p);
    if (intersectSP(s, r)) return abs(r - p);
    return min(abs(s.p - p), abs(s.q - p));
}
lf distanceSS (segment s, segment t) {
    if (intersectSS(s, t)) return 0;
    return min(min(distanceSP(s, t.p), distanceSP(s, t.q)),
        min(distanceSP(t, s.p), distanceSP(t, s.q)));
}
struct polygon {
    vector<pt> pts;
    lf compute_area () {
        lf area = 0;
        for (int i = 1; i + 1 < pts.size(); i++)
            area += cross(pts[i] - pts[0], pts[i + 1] - pts[0]);
        return abs(area) / 2.0;
    }
    // the points are given in the order of counter-clockwise
    bool is_convex () {
        int len = pts.size();
        for (int i = 0; i < len; i++)
            if (ccw(pts[i], pts[(i + 1) % len], pts[(i + 2) % len]) == -1)
                return false;
        return true;
    }
    polygon cut (pt p, pt q) {
        polygon new_polygon;
        for (int i = 0; i < pts.size(); ++i) {
            pt a = pts[i], b = pts[(i + 1) % pts.size()];
            lf pqa = cross(q - p, a - p),
                pqb = cross(q - p, b - p);
            if (pqa >= 0) new_polygon.pts.push_back(a);
            if (pqa * pqb < 0)
                new_polygon.pts.push_back(linesIntersection(p, q, a, b));
        }
        return new_polygon;
    }
    enum {OUT, ON, IN};
    // the points are given in the order of counter-clockwise
    // either convex/non-convex
    int contains (pt &p) {
        bool in = false;
        int n = pts.size();
        for (int i = 0; i < n; i++) {
            pt a = pts[i] - p, b = pts[(i + 1) % n] - p;
            if (imag(a) > imag(b)) swap(a, b);
            if (imag(a) <= 0 && 0 < imag(b))
                if (cross(a, b) < 0) in = ! in ;
            if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
        }
        return in ? IN : OUT;
    }
};


struct circle{
    point center;
    double r;

    bool contain(point &p){
        return abs(center - p) < r + eps;
    }
};

circle min_circle(vector<point> &cloud, int a, int b){
    point center = (cloud[a] + cloud[b]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < b; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        center = three_point_circle( cloud[a], cloud[b], cloud[i] );
        rat = abs(center - cloud[a]);
        C = {center, rat};
    }
    return C;
}

circle min_circle(vector<point> &cloud, int a){
    point center = (cloud[a] + cloud[0]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < a; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, a, i);
    }

    return C;
}

circle min_circle(vector<point> cloud){
    // random_shuffle(cloud.begin(), cloud.end());

    int n = (int)cloud.size();

    for (int i = 1; i < n; ++i){
        int u = rand() % i;
        swap(cloud[u], cloud[i]);
    }

    point center = (cloud[0] + cloud[1]) / double(2.);
    double rat = abs(center - cloud[0]);
    circle C = {center, rat};
    for (int i = 2; i < n; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, i);
    }
    return C;
}
