int lca (int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    //int ans = INT_MAX;
    for (int i = MAXLOG - 1; i >= 0; --i)
        if (depth[dp[a][i]] >= depth[b]) {
            //ans = min(ans, mn[a][i]);
            a = dp[a][i];
        }
    //if (a == b) return ans;
    if (a == b) return a;
    for (int i = MAXLOG - 1; i >= 0; --i)
        if (dp[a][i] != dp[b][i]) {
            //ans = min(ans, mn[a][i]);
            //ans = min(ans, mn[b][i]);
            a = dp[a][i],
            b = dp[b][i];
        }
    //ans = min(ans, mn[a][0]);
    //ans = min(ans, mn[b][0]);
    //return ans;
    return dp[a][0];
}
void dfs (int u, int d, int p = -1) {
    depth[u] = d;
    for(auto v : g[u]) {
        int v = g[u][i].first;
        if (v != p) {
            dfs(v, d + 1, u);
            dp[v][0] = u;
            //mn[v][0] = w;
        }
    }
}
void build (int root, int n) {
    dp[root][0] = 0;
    mn[root][0] = INT_MAX;
    dfs(root, 1);
    for (int j = 0; j < MAXLOG - 1; ++j)
        for(int i = 0; i <= n; ++i) { // nodes
            dp[i][j + 1] = dp[dp[i][j]][j];
            mn[i][j + 1] = min(mn[dp[i][j]][j], mn[i][j]);
        }
}
