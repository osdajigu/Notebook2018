struct pt {
    lf x, y;
    pt () {}
    pt (lf x, lf y): x(x), y(y) {}
};
inline lf x (pt P) { return P.x; }
inline lf y (pt P) { return P.y; }
istream &operator >> (istream & in, pt & p) {
    lf x, y; in >> x >> y;
    p = pt(x, y);
    return in;
}
ostream &operator << (ostream &out, const pt & p) {
    out << int(p.x) << " " << int(p.y);
    return out;
}
pt operator + (const pt &a, const pt & b) {
    return pt(x(a) + x(b), y(a) + y(b));
}
pt operator - (const pt &a, const pt & b) {
    return pt(x(a) - x(b), y(a) - y(b));
}
pt operator * (const lf &b, const pt & a) {
    return pt(x(a) * b, y(a) * b);
}
pt operator * (const pt &a, const lf & b) {
    return pt(x(a) * b, y(a) * b);
}
inline lf norm (pt a) { return x(a) * x(a) + y(a) * y(a); }
inline lf abs (pt a) { return sqrt(norm(a)); }
inline lf dist (pt a, pt b) { return abs(b - a); }
inline bool same (lf a, lf b) { return a + eps > b && b + eps > a; }
inline lf dot (pt a, pt b) { return x(a) * x(b) + y(a) * y(b); }
inline lf cross (pt a, pt b) { return x(a) * y(b) - y(a) * x(b); }
