#include <bits/stdc++.h>
// 求等腰梯形个数 N <= 1000
// 枚举所有连线，求出中垂线和中点，中垂线相同且中点不同，可以构成等腰梯形
// 中垂线方程形如 ax + by = c，注意排序和取 gcd，不要用 y = ax + b
// 注意 map 不是按 value 升序排序
// 时间复杂度 O(N^2logN^2)
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n, ans(-1);
vector<tuple<int, int, int>> perpenb; // perpendicular bisectors
vector<map<pair<int, int>, int>> midpoints; // midpoints of a perpendicular bisector
vector<tuple<int, int, int>> p;

signed main() {
    boost;
    cin >> n;
    for (signed i = 0, x, y, c; i < n; i++) {
        cin >> x >> y >> c;
        p.emplace_back(x << 1, y << 1, c);
    }
    sort(p.begin(), p.end());
    for (signed i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int xi, yi, ci, xj, yj, cj;
            tie(xi, yi, ci) = p[i], tie(xj, yj, cj) = p[j];
            long long x1 = (xi + xj) >> 1, y1 = (yi + yj) >> 1;
            long long vecx = yi - yj, vecy = xj - xi;
            long long x2 = x1 + vecx, y2 = y1 + vecy;
            int a = y2 - y1, b = x1 - x2, c = x1 * y2 - x2 * y1;
            int gcd = __gcd(a, __gcd(b, c));
            a /= gcd, b /= gcd, c /= gcd;
            // error(a, b, c);
            perpenb.emplace_back(a, b, c);
        }
    sort(perpenb.begin(), perpenb.end());
    int cnt = unique(perpenb.begin(), perpenb.end()) - perpenb.begin();
    midpoints.resize(cnt);

    for (signed i = 0; i < n; i++)
        for (signed j = i + 1; j < n; j++) {
            int xi, yi, ci, xj, yj, cj;
            tie(xi, yi, ci) = p[i], tie(xj, yj, cj) = p[j];
            long long x1 = (xi + xj) >> 1, y1 = (yi + yj) >> 1;
            long long vecx = yi - yj, vecy = xj - xi;
            long long x2 = x1 + vecx, y2 = y1 + vecy;
            int a = y2 - y1, b = x1 - x2, c = x1 * y2 - x2 * y1;
            int gcd = __gcd(a, __gcd(b, c));
            a /= gcd, b /= gcd, c /= gcd;
            int pos = lower_bound(perpenb.begin(), perpenb.begin() + cnt, make_tuple(a, b, c)) - perpenb.begin();
            int tmp = midpoints[pos][{x1, y1}];
            midpoints[pos][{x1, y1}] = max(tmp, ci + cj);
        }
    for (auto& mp : midpoints) {
        if (mp.size() < 2) continue;
        vector<int> cs;
        for (auto& i : mp) cs.push_back(i.second);
        sort(cs.begin(), cs.end());
        ans = max(ans, cs[cs.size() - 1] + cs[cs.size() - 2]);
    }
    cout << ans << "\n";
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */