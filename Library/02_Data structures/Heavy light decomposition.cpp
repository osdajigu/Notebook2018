///------------------- O(N), O(log(N)*O(query)) -------------------///
template <class ds>
struct hld {
    graph g;
    vector<int> child, val, depth, pos, up, start;
    int cur;
    ds tree;
    int children (int u, int p = -1) {
        ii best(-1, -1);
        int ans = 1;
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if (v != p) {
                ii cur = ii(children(v, u), v);
                best = max(best, cur);
                ans += cur.first;
            }
        }
        child[u] = best.second;
        return ans;
    }
    void build (int u, int d = 0, int s = 1, int prev = -1, int p = -1) {
        pos[u] = cur++;
        up[u] = prev;
        depth[u] = d;
        start[u] = s;
        if (child[u] != -1)
            build(child[u], d, s, prev, u);
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if (v != child[u] && v != p)
                build(v, d + 1, cur, u, u);
        }
    }
    void update (int u, int val) {
        tree.update(pos[u], val);
    }
    int query (int u, int v) {
        int ans = 0;
        while (start[u] != start[v]) {
            if (depth[u] < depth[v]) swap(u, v);
            ans = max(ans, tree.query(start[u], pos[u]));
            u = up[u];
        }
        if (pos[u] > pos[v]) swap(u, v);
        return max(ans, tree.query(pos[u], pos[v]));
// when updates are on edges use:
//        if (pos[u] == pos[v]) return ans;
//        return max(ans, tree.query(pos[u] + 1, pos[v]));
    }
    hld (graph &g, int root, vector<int> &val) :
            g(g), val(val), cur(1), tree(ds(1, val.size())) {
// if segtree from 0 wanted, change cur and s = 0
        child.assign(g.size(), 0);
        pos.assign(g.size(), 0);
        up.assign(g.size(), 0);
        depth.assign(g.size(), 0);
        start.assign(g.size(), 0);
        children(root);
        build(root);
        for (int i = 1; i < val.size(); ++i)
            tree.update(pos[i], val[i]);
    }
};
