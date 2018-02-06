int f[MAX];
int kmp (string &a, string &b) {
    int matches = 0;
    f[0] = -1;
    for (int i = 0, j = -1; i < b.size(); ) {
        while (j > -1 && b[j] != b[i]) j = f[j];
        ++i, ++j;
        f[i] = j;
    }
    for (int i = 0, j = 0; i < a.size(); ) {
        while (j > -1 && b[j] != a[i]) j = f[j];
        ++i, ++j;
        if (j == b.size()) matches++, j = f[j];
    }
    return matches;
}
