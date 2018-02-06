struct point {
    lf x, y;
    point () : x(0), y(0) {}
    point (lf x, lf y) : x(x), y(y) {}
    bool operator < (const point &other) const {
        return y < other.y;
    }
};
int cmp (const point &a, const point &b) {
    return a.x < b.x;
}
/// cambiar para que se manejen sin raiz...
lf solve (vector<point> &p) {
    sort(p.begin(), p.end(), cmp);
    set<point> ys;
    int left = 0;
    lf h = numeric_limits<lf>::max()/3;
    ys.insert(p[0]);
    for (int i = 1; i < p.size(); i++) {
        while (left < i && p[i].x - p[left].x > h)
            ys.erase(p[left++]);
        auto it = ys.lower_bound( {p[i].x - h, p[i].y - h} );
        for (; it != ys.end() && p[i].y + h >= it->y; it++)
            h = min(h, hypot(p[i].x - it->x, p[i].y - it->y));
        ys.insert(p[i]);
    }
    return h;
}
