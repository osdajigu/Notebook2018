int idx[MAX], low[MAX];
bool in_stack[MAX];
graph g;

int scc (int &index, int u, stack<int> &st) {
    idx[u] = low[u] = ++index;
    st.push(u);
    in_stack[u] = true;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if ( idx[v] == -1 ) {
            scc(index, v, st);
            low[u] = min(low[u], low[v]);
        } else if ( in_stack[v] )
            low[u] = min(low[u], idx[v]);
    }
    if (low[u] == idx[u]) {
        int v;
        do {
            v = st.top(); st.pop();
            //tag v
            in_stack[v] = false;
        } while (v != u);
    }
}
