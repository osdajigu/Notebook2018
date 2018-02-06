///------------------- O(|E|*sqrt(|V|)) -------------------///
struct hopcroft_karp {
    int l, r;
    vector<int> last, prev, head, matching, d;
    vector<bool> used, vis;
    hopcroft_karp(int l, int r) :
        l(l), r(r), last(l, -1), matching (r, -1), d(l), used(l), vis(l) {}
    // u -> 0 to l, v -> 0 to r
    void add_edge(int u, int v) {
        head.push_back(v);
        prev.push_back(last[u]);
        last[u] = prev.size()-1;
    }
    void bfs() {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        for(int u = 0; u < l; u++) {
            if(!used[u]) {
                q.push(u);
                d[u] = 0;
            }
        }
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int e = last[u]; e >= 0; e = prev[e]) {
                int v = matching[ head[e] ];
                if(v >= 0 && d[v] < 0) {
                    d[v] = d[u]+1;
                    q.push(v);
                }
            }
        }
    }
    bool dfs(int u) {
        vis[u] = true;
        for(int e = last[u]; e >= 0; e = prev[e]) {
            int v = head[e];
            int k = matching[v];
            if(k < 0 || ( !vis[k] && d[k] == d[u]+1 && dfs(k) )) {
                matching[v] = u;
                used[u] = true;
                return true;
            }
        }
        return false;
    }
    int max_matching() {
        int ans = 0;
        while(true) {
            bfs();
            fill(vis.begin(), vis.end(), false);
            int f = 0;
            for(int u = 0; u < l; u++)
                if(!used[u] && dfs(u)) f++;
            if(f == 0) return ans;
            ans += f;
        }
        return 0;
    }
};
