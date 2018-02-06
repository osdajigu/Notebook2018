int CCW = 1;
int CW = -1;
int ONB = 2; // ONLINE_BACK
int ONF = -2; //ONLINE_FRONT
int ONS = 0; //ON_SEGMENT

int ccw (pt p, pt p1, pt p2) {
    pt a = p1 - p;
    pt b = p2 - p;
    if (cross(a, b) > eps) return CCW;
    if (cross(a, b) < -eps) return CW;
    if (dot(a, b) < -eps) return ONB;
    if (norm(a) < norm(b)) return ONF;
    return ONS;
}
struct polygon {
    vector < pt > pts;
};
enum {OUT, ON, IN};
// the points are given in the order of counter-clockwise
int contains (polygon &pol, pt &p) {
    int len = pol.pts.size();
    int v1 = ccw(pol.pts[len - 1], pol.pts[0], p);
    int v2 = ccw(pol.pts[0], pol.pts[1], p);
    if (v1 == CW || v2 == CW) return OUT;
    if (v1 == ONS || v2 == ONS) return ON;
    int r = len - 1, l = 1;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        v1 = ccw(pol.pts[0], pol.pts[m], p);
        if (v1 == CCW) l = m;
        else r = m;
    }
    v1 = ccw(pol.pts[l], pol.pts[r], p);
    if (v1 == CCW) return IN;
    if (v1 == ONS) return ON;
    return OUT;
}
