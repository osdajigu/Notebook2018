#define cross(A,B)		imag(conj((A))*(B))
#define x(P)		real(P)
#define y(P)		imag(P)
struct polygon {
    vector<pt> p, ch;
    bool cmpt (pt &p, pt &q) {
        if (x(p) != x(q)) return x(p) < x(q);
        return y(p) < y(q);
    }

    void delete_repetead() {
        vector<pt> aux;
        sort(p.begin(), p.end(), cmpt);
        for(pt &i : p) {
            if(aux.empty() || aux.back() != i)
                aux.push_back(i);
        }
        p = aux;
    }
    // be careful, cross may overflow with int, use long long instead
    int orientation (pt &p, pt &q, pt &r) {
        return cmp(cross(q-p, r-p), 0); // 0->colineal, 1->left, -1->right
    }
    //result in counter-clockwise orientation
    void convex_hull () {
        sort(p.begin(), p.end(), cmpt);
        ch.resize(p.size());
        int k = 0;
        for (int i = 0; i < n; ++i) {
            // if colineal are needed, use < and remove repeated points
            while (k >= 2 && orientation(ch[k - 2], ch[k - 1], p[i]) < 0)
                --k;
            ch[k++] = p[i];
        }
        for (int i = n - 2, t = k + 1; i >= 0; --i) {
            // if colineal are needed, use < and remove repeated points
            while (k >= t && orientation(ch[k - 2], ch[k - 1], p[i]) < 0)
                --k;
            ch[k++] = p[i];
        }
        ch.resize(k-1);
    }

    lf compute_area () {
        lf area = 0;
        for (int i = 1; i + 1 < p.size(); i++)
            area += cross(p[i] - p[0], p[i + 1] - p[0]);
        return abs(area) / 2.0;
    }

    lf compute_perimeter() {
        lf per = 0;
        int n = p.size();
        for(int i = 0; i < n; i++) {
            per += abs(p[i] - p[(i+1)%n]);
        }
        return per;
    }


};
