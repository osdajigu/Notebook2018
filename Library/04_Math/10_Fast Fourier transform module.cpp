const int mod = 998244353; /// mod = c*2^k+1
/// find g = primitive root of mod.
const int root = 15311432; /// (g^c)%mod
const int root_1 = 469870224; /// inverse of root
const int root_pw = 1 << 23; /// 2^k

void fft(vector<int> &a, bool inv = 0) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int c = n >> 1;
    for (; j >= c; c >>= 1) j -= c;
    j += c;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    int wlen = inv ? root_1 : root;
    for (int i = len; i < root_pw; i <<= 1) wlen = (1 LL * wlen * wlen) % mod;
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < (len >> 1); j++) {
        int u = a[i + j], v = (a[i + j + (len >> 1)] * 1 LL * w) % mod;
        a[i + j] = u + v < mod ? u + v : u + v - mod;
        a[i + j + (len >> 1)] = u - v >= 0 ? u - v : u - v + mod;
        w = (w * 1 LL * wlen) % mod;
      }
    }
  }
  if (inv) {
    int nrev = pow(n);
    for (int i = 0; i < n; i++) a[i] = (a[i] * 1 LL * nrev) % mod;
  }
}
vector<int> mul (const vector <int> a,
  const vector <int> b) {
  vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max(a.size(), b.size())) n <<= 1;
  n <<= 1;
  fa.resize(n); fb.resize(n);
  fft(fa);
  fft(fb);
  for (int i = 0; i < n; i++) fa[i] = (1ll * fa[i] * fb[i]) % mod;
  fft(fa, 1);
  return fa;
}
