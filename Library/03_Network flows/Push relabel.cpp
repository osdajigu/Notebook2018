///------------------- O(|V|^3) -------------------///
typedef long long ll;
struct edge {
	int u, v, cap, flow, index;
	edge(int u, int v, int cap, int flow, int index) :
			u(u), v(v), cap(cap), flow(flow), index(index) {}
};
struct push_relabel {
	int n;
	vector< vector<edge> > g;
	vector<ll> excess;
	vector<int> dist, active, count;
	queue<int> q;
	push_relabel(int n) : n(n), g(n), excess(n), dist(n), active(n),
                          count(2 * n) {}
	void add_edge(int u, int v, int cap) {
		g[u].push_back(edge(u, v, cap, 0, g[v].size()));
		if (u == v) g[u].back().index++;
		g[v].push_back(edge(v, u, 0, 0, g[u].size() - 1));
	}
	void enqueue(int v) {
		if (!active[v] && excess[v] > 0) {
			active[v] = true;
			q.push(v);
		}
	}
	void push(edge &e) {
		int amt = int(min(excess[e.u], ll(e.cap - e.flow)));
		if (dist[e.u] <= dist[e.v] || amt == 0) return;
		e.flow += amt;
		g[e.v][e.index].flow -= amt;
		excess[e.v] += amt;
		excess[e.u] -= amt;
		enqueue(e.v);
	}
	void gap(int k) {
		for (int v = 0; v < n; v++) {
			if (dist[v] < k) continue;
			count[dist[v]]--;
			dist[v] = max(dist[v], n + 1);
			count[dist[v]]++;
			enqueue(v);
		}
	}
	void relabel(int v) {
		count[ dist[v] ]--;
		dist[v] = 2 * n;
		for (int i = 0; i < g[v].size(); i++)
			if (g[v][i].cap - g[v][i].flow > 0)
				dist[v] = min(dist[v], dist[ g[v][i].v ] + 1);
		count[ dist[v] ]++;
		enqueue(v);
	}
	void discharge(int v) {
		for (int i = 0; excess[v] > 0 && i < g[v].size(); i++)
			push(g[v][i]);
		if (excess[v] > 0) {
			if (count[dist[v]] == 1)
				gap(dist[v]);
			else
				relabel(v);
		}
	}
	ll max_flow(int s, int t) {
		count[0] = n - 1;
		count[n] = 1;
		dist[s] = n;
		active[s] = active[t] = true;
		for (int i = 0; i < g[s].size(); i++) {
			excess[s] += g[s][i].cap;
			push(g[s][i]);
		}
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			active[v] = false;
			discharge(v);
		}
		ll res = 0;
		for (int i = 0; i < g[s].size(); i++)
			res += g[s][i].flow;
		return res;
	}
};
