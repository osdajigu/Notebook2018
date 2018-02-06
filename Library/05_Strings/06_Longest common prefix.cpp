namespace suffix {
    int lcp[MAX];
    //lcp[i] means the maximum common prefix of sa[i] and sa[i - 1]
    void build_lcp(){
        int l = 0;
        lcp[0] = 0;
        for(int i = 0; i < n; i++) {
            if(i == sa[0]) continue;
            while(s[i + l] == s[sa[ ra[i]-1] + l]) l++;
            lcp[ ra[i] ] = l;
            l = max(l-1, 0);
        }
    }
}
