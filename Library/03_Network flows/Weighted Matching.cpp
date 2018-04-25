// Complexity:
//   O(n^3).
//   Much faster than the Kuhn-Munkres algorithm.
// Note:
//   It finds minimum cost maximal matching.
//   To find the minimum cost non-maximal matching,
//   we add n dummy vertices to the right side.
typedef int type;
struct matching_weighted {
    int l, r;
    vector<vector<type>> c;
    matching_weighted(int l, int r) : l(l), r(r), c(l, vector<type>(r)) {
        assert(l <= r);
    }
    inline add_edge(int a, int b, type cost) {
        c[a][b] = cost;
    }

    type matching() {
        vector<type> v(r), dist(r); // v: potential
        vector<int> ml(l, -1), mr(r, -1); // matching pairs
        vector<int> idx(r), prev(r);
        iota(idx.begin(), idx.end(), 0);
        auto residue = [ & ](int i, int j) {
            return c[i][j] - v[j];
        };
        for (int f = 0; f < l; ++f) {
            for (int j = 0; j < r; ++j) {
                dist[j] = residue(f, j);
                prev[j] = f;
            }
            ll w;
            int j, l;
            for (int s = 0, t = 0;;) {
                if (s == t) {
                    l = s;
                    w = dist[ idx[t++] ];
                    for (int k = t; k < r; ++k) {
                        j = idx[k];
                        ll h = dist[j];
                        if (h <= w) {
                            if (h < w) {
                                t = s;
                                w = h;
                            }
                            idx[k] = idx[t];
                            idx[t++] = j;
                        }
                    }
                    for (int k = s; k < t; ++k) {
                        j = idx[k];
                        if (mr[j] < 0) goto aug;
                    }
                }
                int q = idx[s++], i = mr[q];
                for (int k = t; k < r; ++k) {
                    j = idx[k];
                    ll h = residue(i, j) - residue(i, q) + w;
                    if (h < dist[j]) {
                        dist[j] = h;
                        prev[j] = i;
                        if (h == w) {
                            if (mr[j] < 0) goto aug;
                            idx[k] = idx[t];
                            idx[t++] = j;
                        }
                    }
                }
            }
            aug: for (int k = 0; k < l; ++k)
                v[ idx[k] ] += dist[ idx[k] ] - w;
            int i;
            do {
                mr[j] = i = prev[j];
                swap(j, ml[i]);
            } while (i != f);
        }
        type opt = 0;
        for (int i = 0; i < l; ++i)
            opt += c[i][ml[i]]; // (i, ml[i]) is a solution
        return opt;
    }
};
