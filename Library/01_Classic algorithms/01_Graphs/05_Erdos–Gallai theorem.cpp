bool erdos (vector<int> &d) {
    ll sum = 0;
    for (int i = 0; i < d.size(); ++i) sum += d[i];
    if (sum & 1)
        return false;
    sort(d.rbegin(), d.rend());
    ll left = 0, right = 0;
    for (int k = 1, i = d.size() - 1; k <= d.size(); ++k) {
        left += d[k - 1];
        if (k > i) right -= d[++i];
        while (i >= k && d[i] < k + 1) right += d[i--];
        if (left > 1ll * k * (k - 1) + 1ll * k * (i - k + 1) + right)
            return false;
    }
    return true;
}
