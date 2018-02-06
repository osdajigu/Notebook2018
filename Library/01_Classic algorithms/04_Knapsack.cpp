//benefit, weight
int P[MAX], W[MAX], dp[MAX_W];
int knapsack (int MW) {
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < N; ++i)
        for (int j = W[i]; j <= MW; ++j)
            dp[j] = max(dp[j], dp[j - W[i]] + P[i]);
    cout << dp[MW] << '\n';
}
