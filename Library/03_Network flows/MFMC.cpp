template <class type>
struct edge {
    int u, v, cap, flow;
    type cost;
    edge() {}
    edge(int u, int v, type cost, int cap, int flow) :
        u(u), v(v), cost(cost), cap(cap), flow(flow) {}
};
const int INF = INT_MAX/3;
template <class type> // type of cost
struct mcmf {
    int n;
    vector< edge<type> > ed;
    vector< vector<int> > g;
    vector<int> p;
    vector<type> d, phi;
    mcmf(int n) : n(n), g(n), p(n), d(n), phi(n) {}
    void add_edge(int u, int v, int cap, type cost) {
        g[u].push_back(ed.size());
        ed.push_back(edge<type>(u, v, cost, cap, 0));
        g[v].push_back(ed.size());
        ed.push_back(edge<type>(v, u, -cost, 0, 0));
    }
    bool dijkstra(int source, int sink) {
        fill(d.begin(), d.end(), INF);
        fill(p.begin(), p.end(), -1);
        set< pair<type, int> > q;
        d[source] = 0;
        for(q.insert(make_pair(d[source], source)); q.size();) {
            int u = (*q.begin()).second; q.erase(q.begin());
            for(int i = 0; i < g[u].size(); i++) {
                edge<type>& e = ed[g[u][i]];
                type nd = d[e.u]+e.cost+phi[e.u]-phi[e.v];
                if(0 < (e.cap-e.flow) && nd < d[e.v]) {
                    q.erase(make_pair(d[e.v], e.v));
                    d[e.v] = nd;
                    p[e.v] = g[u][i];
                    q.insert(make_pair(d[e.v], e.v));
                }
            }
        }
        for(int i = 0; i < n; i++) phi[i] = min(INF, phi[i]+d[i]);
        return d[sink] != INF;
    }
    pair<int, type> max_flow(int source, int sink) {
        type mc = 0;
        int mf = 0;
        fill(phi.begin(), phi.end(), 0);
        while(dijkstra(source, sink)) {
            int flow = INF;
            for(int v = p[sink]; v != -1; v = p[ed[v].u]) {
                flow = min(flow, ed[v].cap-ed[v].flow);
            }
            for(int v = p[sink]; v != -1; v = p[ed[v].u]) {
                edge<type>& e1 = ed[v];
                edge<type>& e2 = ed[v^1];
                mc += e1.cost*flow;
                e1.flow += flow;
                e2.flow -= flow;
            }
            mf += flow;
        }
        return make_pair(mf, mc);
    }
};
