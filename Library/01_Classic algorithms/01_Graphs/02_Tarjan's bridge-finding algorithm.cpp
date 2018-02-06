set<int> articulation;
int idx[MAX], low[MAX];
graph g;

void bridges(int &index, int u, int p = -1) {
    idx[u] = low[u] = ++index;
    int children = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (idx[v] == -1) {
            children++;
            bridges(index, v, u);
            low[u] = min(low[u], low[v]);
            if(p != -1 && low[v] >= idx[u])
                articulation.insert(v);
            if(low[v] > idx[u]) {
                //bridge
            }
        }
        else if (v != p)
            low[u] = min(low[u], idx[v]);
    }
    if(p == -1 && children > 1)
        articulation.insert(u);
}
