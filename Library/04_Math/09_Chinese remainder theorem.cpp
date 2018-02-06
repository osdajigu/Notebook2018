// finds a suitable x that meets: x is congruent to a_i mod n_i
namespace crt {
    int a[MAX], n[MAX], e;
    int solve () {
        int A = 1, x = 0;
        for (int i = 0; i < e; i++) A *= n[i];
        for (int i = 0; i < e; i++) {
            int ni = A / n[i];
            int yi = inverse(ni, n[i]);
            x += (ni * yi * a[i]) % A;
        }
        return x % A;
    }
}
