///------------------- O(|E|*|MAXFLOW|) -------------------///
struct edge {
    int v, cap, inv;
    edge() {}
    edge(int v, int cap, int inv) : v(v), cap(cap), inv(inv) {}
};
struct ford_fulkerson {
    int n;
    vector< vector<edge> > g;
    vector<bool> seen;
    ford_fulkerson(int n) : n(n), g(n), seen(n) {}
    int augment(int u, int cur, int t) {
        if(u == t) return cur;
        if(seen[u]) return false;
        seen[u] = true;
        int ans;
        for(int i = 0; i < g[u].size(); i++) {
            edge& e = g[u][i];
            if(e.cap > 0 && (ans = augment(e.v, min(cur, e.cap), t))) {
                e.cap -= ans;
                g[e.v][e.inv].cap += ans;
                return ans;
            }
        }
        return 0;
    }
    int max_flow(int s, int t) {
        int res = 0, aug;
        while(true) {
            fill(seen.begin(), seen.end(), false);
            aug = augment(s, INT_MAX, t);
            if(aug == 0) break;
            res += aug;
        }
        return res;
    }
    void add_edge(int u, int v, int c) {
        g[u].push_back(edge(v, c, g[v].size()));
        g[v].push_back(edge(u, 0, g[u].size()-1));
    }
};
