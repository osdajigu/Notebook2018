void go (int u) {
    while (g[u].size()) {
        int v = g[u].front();
        g[u].pop_front();
        go(v);
    }
    tour[len++] = u;
}
//tour size must be as large as the number of edges
bool eulerian (vector<deque<int>> &g) { // directed graph
    int one_in = 0, one_out = 0, start = -1;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (out[i] && start == -1) start = i;
        if (out[i] - in[i] == 1) one_out++, start = i;
        else if (in[i] - out[i] == 1) one_in++;
        else ok &= in[i] == out[i];
    }
    ok &= one_in == one_out && one_in <= 1;
    if (ok) {
        len = 0;
        go(start);
        if (len == edges + 1)
            return true; // path is in tour[]. Must be reversed
    }
    return false;
}
