#include <bits/stdc++.h>
// https://codeforces.com/contest/2098/problem/E
// congruence, exgcd, crt

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

// 满足 ax + by = gcd(a, b) 的整数解 x
// s = gcd(a, b), y = (s - ax) / b
// ax + by = c 有整数解的充要条件：c % gcd(a, b) = 0
constexpr pair<long long, long long> exgcd(long long a, long long b) {
    a %= b;
    if (a < 0) a += b;
    if (a == 0) return {b, 0};
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        swap(s, t);
        swap(m0, m1);
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// 同余方程 ax == c (mod b) 的最小正整数解
// 即解不定方程 ax + by = c   (a, b, c >= 0)
pair<long long, long long> exexgcd(long long a, long long b, long long c) {
    long long g = gcd(a, b);
    if (c % g) return {-1, -1};  // 无解
    a /= g, b /= g, c /= g;
    auto [_, x] = exgcd(a, b);  // a1x + b1y = 1 (since a1, b1 are coprime now)
    long long y = (c - a * x) / b;
    x = ((x * c % b) + b * g) % b;  // a1x == 1 (mod b1)
    y = (c - a * x) / b;
    return {x, y};
}

void solveOne(int ncase) {
    long long n, x, y, vx, vy;
    cin >> n >> x >> y >> vx >> vy;
    long long gv = __gcd(vx, vy);
    vx /= gv, vy /= gv;

    // x + tx * vx == 0 (mod n)
    auto [tx, _] = exexgcd(vx, n, (-x % n + n) % n);
    // y + ty * vy == 0 (mod n)
    auto [ty, __] = exexgcd(vy, n, (-y % n + n) % n);

    if (tx == -1 || ty == -1) {
        cout << "-1\n";
        return;
    }

    long long n1 = n / gcd(vx, n);
    long long n2 = n / gcd(vy, n);

    // k == tx (mod n1), k = ty (mod n2), crt
    // k = p * n1 + tx = q * n2 + ty
    // p * n1 - q * n2 = ty - tx
    int g = gcd(n1, n2);
    if ((ty - tx) % g != 0) {
        cout << "-1\n";
        return;
    }
    auto [p, q] = exexgcd(n1, n2, ty - tx);
    q = -q;
    long long t = p * n1 + tx;

    x = x + t * vx, y = y + t * vy;

    long long res = 0;
    res += (x / n) - 1;
    res += (y / n) - 1;
    res += (x + y) / (n * 2);
    res += abs(x - y) / (n * 2);
    cout << res << "\n";
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */