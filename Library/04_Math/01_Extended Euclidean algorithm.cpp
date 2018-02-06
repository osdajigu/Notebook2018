int eea (int a, int b, int& x, int& y) {
    int xx = y = 0; int yy = x = 1;
    while (b) {
        int q = a / b; int t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    return a;
}
int inverse (int a, int n) {
    int x, y;
    int g = eea(a, n, x, y);
    if (g > 1)
        return -1;
    return (x % n + n) % n;
}
