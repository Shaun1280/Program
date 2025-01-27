#include <bits/stdc++.h>
#define int long long
//https://www.luogu.com.cn/problem/CF1355E
using namespace std;

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int tc, n, a, r, m;
array<int, MAXN> h;

inline int calc(int tmpH) {
    int inc = 0, dec = 0;
    for (int i = 1; i <= n; i++) {
        if (h[i] > tmpH) dec += h[i] - tmpH;
        else inc += tmpH - h[i];
    }
    int res = m * min(inc, dec);
    if (inc > dec) res += a * (inc - dec);
    else res += r * (dec - inc);
    return res;
}

inline void tripartition() {
    int l = 1e18, r = 0, res = 1e18;
    for (int i = 1; i <= n; i++)
        l = min(l, h[i]), r = max(r, h[i]);
    while (r - l >= 3) {
        int lmid = (l + l + r) / 3;
        int rmid = (l + r + r) / 3;
        int lval = calc(lmid), rval = calc(rmid);
        if (lval < rval) r = rmid;
        else l = lmid;
    }
    for (int i = l; i <= r; i++)
        res = min(res, calc(i));
    cout << res << endl;
}

signed main() {
    cin >> n >> a >> r >> m;
    m = min(m, a + r);
    for (int i = 1; i <= n; i++) cin >> h[i];
    tripartition();
    return 0;
}