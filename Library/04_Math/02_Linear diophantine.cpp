bool diophantine (ll a, ll b, ll c, ll &x, ll &y) {
    ll g = __gcd(abs(a), abs(b));
    if (c % g) return false;
    eea(abs(a), abs(b), x, y);
    x *= c / g;
    if (a < 0) x *= -1;
    y *= c / g;
    if (b < 0) y *= -1;
    return true;
}
//finds the first k | x + b * k / gcd(a, b) >= val
ll greater_or_equal_than (ll a, ll b, ll x, ll val) {
    ll g = __gcd(abs(a), abs(b));
    return ceil(1.0 * (val - x) * g / b);
}
ll less_or_equal_than (ll a, ll b, ll x, ll val) {
    ll g = __gcd(abs(a), abs(b));
    return floor(1.0 * (val - x) * g / b);
}
void get_xy (ll a, ll b, ll &x, ll &y, ll k) {
    ll g = __gcd(abs(a), abs(b));
    x = x + b / g * k;
    y = y - a / g * k;
}
