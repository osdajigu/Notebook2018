struct matrix {
    const int MOD = 1000000007;
    const int N = 2;
    int m[N][N];
    int f, c;
    matrix (int f = N, int c = N, bool iden = false) : f(f), c(c) {
        for (int i = 0; i < f; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = 0;
        if (iden)
            for(int i = 0; i < f; i++) m[i][i] = 1;
    }
    matrix operator * (const matrix &o) {
        matrix ret(f, o.c);
        for(int i = 0; i < f; ++i)
            for(int j = 0; j < o.c; ++j) {
                ll r = 0;
                for(int k = 0; k < c; ++k)
                    r = (r + m[i][k] * 1ll * o.m[k][j]) % MOD;
                ret.m[i][j] = r;
            }
        return ret;
    }
};
