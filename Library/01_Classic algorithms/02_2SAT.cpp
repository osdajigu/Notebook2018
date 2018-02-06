struct sat2 {
    graph g, rg;
    vector<int> c;
    vector<bool> ans;
    int tag, n, sz;
    stack<int> st;
    sat2(int n) : n(n), sz(2*n), g(2*n), rg(2*n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    int neg(int u) {
        return (n+u)%sz;
    }
    void implication(int u, int v) { // to add (u or v)
        add_edge(neg(u), v);
        add_edge(neg(v), u);
    }
    void diff(int u, int v) {
        implication(u, v);
        implication(neg(u), neg(v));
    }
    void eq(int u, int v) {
        diff(neg(u), v);
    }
    void dfs(int u, vector< vector<int> > &g, bool first) {
        c[u] = tag;
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(c[v] == -1)
                dfs(v, g, first);
        }
        if(first) st.push(u);
    }
    bool possible() {
        tag = 0;
        ans.assign(n, 0);
        c.assign(sz, -1);
        for(int i = 0; i < sz; i++) {
            if(c[i] == -1)
                dfs(i, g, true);
        }
        c.assign(sz, -1);
        tag = 0;
        while(st.size()) {
            int u = st.top(); st.pop();
            if(c[u] != -1) continue;
            ++tag;
            dfs(u, rg, false);
        }
        for(int i = 0; i < n; i++) {
            if(c[i] == c[neg(i)])
                 return false;
            ans[i] = c[i] > c[neg(i)];
        }
        return true;
    }
};
/** Additional functions
implication -> u or v and not u or not v
void eq(int u, int v){
    implication(u, v);
    implication(v, u);
}
void diff(int u, int v){
    eq(u, neg(v));
}
**/
