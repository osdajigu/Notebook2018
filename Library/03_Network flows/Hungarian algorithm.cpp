///------------------- O(|V|*|E|) -------------------///
struct hungarian_bipartite {
    int l, r;
    vector< vector<int> > g;
    vector<bool> seen;
    vector<int> match; // match[i] is the left matching of right node i
    hungarian_bipartite(int l, int r) : l(l), r(r), seen(l), match(l+r, -1), g(l+r) {}
    // [0-l) left, [l, r) right
    // a and b are 0-indexed
    void add_edge(int a, int b) {
        g[a].push_back(l+b);
        g[l+b].push_back(a);
    }
    bool go(int u) {
        if(seen[u]) return false;
        seen[u] = true;
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(match[v] == -1 || go(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }
    int max_matching() {
        int ans = 0;
        for(int i = 0; i < l; i++) {
            fill(seen.begin(), seen.end(), false);
            ans += go(i);
        }
        return ans;
    }
};
