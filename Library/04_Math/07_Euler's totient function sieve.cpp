for (int i = 1; i < MN; i++)
    phi[i] = i;
for (int i = 1; i < MN; i++)
    if (prime[i])
        for (int j = i; j < MN; j += i)
            phi[j] -= phi[j] / i;
