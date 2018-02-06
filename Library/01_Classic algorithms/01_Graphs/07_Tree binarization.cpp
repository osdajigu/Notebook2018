void add(int u, int v, int w) {
    ng[u].push_back(ii(v, w));
//    ng[v].push_back(ii(u, w));
}
void binarize (int u, int p = -1) {
    int last = u;
    bool f = true;
    for(auto x : g[u]) {
        int v = x.first, w = x.second, node = ng.size();
        if(v == p) continue;
        if(f) {
            add(u, v, w);
        } else {
            ng.push_back(vector<ii>());
            add(last, node, 0);
            add(node, v, w);
            last = node;
        }
        binarize(v, u);
        f = false;
    }
}
