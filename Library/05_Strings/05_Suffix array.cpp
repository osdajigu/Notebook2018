namespace suffix {
    string s;
    int n;
    int ra[MAX], tra[MAX];
    int sa[MAX], tsa[MAX];
    int c[MAX];
    void counting_sort (int k) {
        int sum, maxi = max(300, n);
        memset(c, 0, sizeof c);
        for (int i = 0; i < n; i++)
            c[i + k < n ? ra[i + k] : 0]++;
        for (int i = sum = 0; i < maxi; i++) {
            int t = c[i]; c[i] = sum; sum += t; }
        for (int i = 0; i < n; i++)
            tsa[c[sa[i]+k < n ? ra[sa[i]+k] : 0]++] = sa[i];
        for (int i = 0; i < n; i++)
            sa[i] = tsa[i];
    }
    //remember to add the '$'
    void build_sa () {
        n = s.size();
        int r;
        for (int i = 0; i < n; i++) ra[i] = s[i];
        for (int i = 0; i < n; i++) sa[i] = i;
        for (int k = 1; k < n; k <<= 1) {
            counting_sort(k);
            counting_sort(0);
            tra[sa[0]] = r = 0;
            for (int i = 1; i < n; i++)
                tra[sa[i]] = (ra[sa[i]] == ra[sa[i-1]] &&
                              ra[sa[i]+k] == ra[sa[i-1]+k]) ? r : ++r;
            for (int i = 0; i < n; i++)
                ra[i] = tra[i];
            if (ra[sa[n-1]] == n-1) break;
        }
    }
}
