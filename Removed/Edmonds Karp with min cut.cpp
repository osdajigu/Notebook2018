///------------------- O(|V|*|E|^2) -------------------///
struct edge {
	int v, cap, inv;
	edge() {}
	edge(int v, int cap, int inv) : v(v), cap(cap), inv(inv) {}
};
struct edmons_karp {
	vector< vector<edge> > g;
	vector<int> from;
	vector<bool> color;
	int n;
	edmons_karp(int n) : n(n), g(n), color(n), from(n) {}
	// call flood (source) to color one node
	// component of min cut
	void flood(int u) {
		if (color[u]) return;
		color[u] = true;
		for(int i = 0; i < g[u].size(); i++) {
            edge &e = g[u][i];
			if (e.cap > 0)
                flood(e.v);
		}
	}
	int max_flow(int s, int t) {
		int res = 0;
		while(1) {
			fill(from.begin(), from.end(), -1);
			queue<int> q;
			q.push(s);
			from[s] = -2;
			for(int u; q.size(); q.pop()) {
				u = q.front();
				for(int i = 0; i < g[u].size(); i++) {
                    edge &e = g[u][i];
					if(from[e.v] == -1 && e.cap) {
						from[e.v] = e.inv;
						q.push(e.v);
					}
				}
			}
			if (from[t] == -1) break;
			int aug = INT_MAX;
			for (int i = t, j; i != s; i = j) {
				j = g[i][ from[i] ].v;
				aug = min(aug, g[j][ g[i][ from[i] ].inv ].cap);
			}
			for (int i = t, j; i != s; i = j) {
				j = g[i][ from[i] ].v;
				g[j][ g[i][from[i] ].inv ].cap -= aug;
				g[i][ from[i] ].cap += aug;
			}
			res += aug;
		}
		return res;
	}
	void add_non_dir_edge(int a, int b, int c) {
		g[a].push_back(edge(b, c, g[b].size()));
		g[b].push_back(edge(a, c, g[a].size() - 1));
	}
	void add_edge(int a, int b, int c) {
		g[a].push_back(edge(b, c, g[b].size()));
		g[b].push_back(edge(a, 0, g[a].size() - 1));
	}
};

