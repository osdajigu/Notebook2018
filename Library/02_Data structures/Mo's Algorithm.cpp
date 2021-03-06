// Requires add(), delete() and get_ans()
struct query {
    int l, r, idx;
    query (int l, int r, int idx) : l(l), r(r), idx(idx) {}
};
int S; // s = sqrt(n)
bool cmp (query a, query b) {
    if (a.l/S != b.l/S) return a.l/S < b.l/S;
    return a.r > b.r;
}
S = sqrt(n); // n = size of array
sort(q.begin(), q.end(), cmp);
int l = 0, r = -1;
for (int i = 0; i < q.size(); ++i) {
    while (r < q[i].r) add(++r);
    while (l > q[i].l) add(--l);
    while (r > q[i].r) del(r--);
    while (l < q[i].l) del(l++);
    ans[q[i].idx] = get_ans();
}
