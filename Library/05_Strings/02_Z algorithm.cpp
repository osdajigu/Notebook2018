//z[i] is the length of the longest substring starting from s[i]
//which is also a prefix of s
//substring from i is a suffix if z[i] == n - i
//call with z_algorithm(a+"$"+b, z)
vector<int> z_algorithm (string &s) {
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = max(0, min(z[i - x], y - i + 1));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            x = i, y = i + z[i], z[i]++;
    }
    return z;
}
