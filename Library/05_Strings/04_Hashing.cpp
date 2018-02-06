typedef long long ll;
typedef pair<int, int> ii;
const int MOD[] = {1000234999, 1000567999}; //1000111997, 1000777121
const ii BASE = ii(256, 256);
const ii IBASE = ii(222708574, 754334468); //167987562, 621576415
#define addt(a, b, x) (((a) + (b)) % MOD[x])
#define subt(a, b, x) (((a) - (b) + MOD[x]) % MOD[x])
#define mult(a, b, x) ((ll(a) * ll(b)) % MOD[x])
#define add(a, b) ii(addt(a.first, b.first, 0), addt(a.second, b.second,1))
#define mul(a, b) ii(mult(a.first, b.first, 0), mult(a.second, b.second,1))
#define sub(a, b) ii(subt(a.first, b.first, 0), subt(a.second, b.second,1))

ii p[MAXN], invp[MAXN];
void prepare () {
    p[0] = invp[0] = ii(1, 1);
    for (int i = 1; i < MAXN; ++i) {
        p[i] = mul(p[i - 1], BASE);
        invp[i] = mul(invp[i - 1], IBASE);
    }
}
template <class container>
struct hs {
    vector<ii> code;
    hs (container &s) {
        code.resize(s.size());
        code[0] = ii(s[0], s[0]);
        for (int i = 1; i < s.size(); ++i)
            code[i] = add(code[i - 1], mul(ii(s[i], s[i]), p[i]));
    }
    ii query (int l, int r) {
        return mul(sub(code[r], (l ? code[l - 1] : ii(0, 0))), invp[l]);
    }
};
