#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1222 P1222 三角形
using namespace std;

constexpr int MAXN = 2e3 + 3;
constexpr double EPS = DBL_EPSILON;

struct Triangle {
    /*@param x1 上顶x坐标 @param y1 上顶y坐标*/
    int x1, y1;
    /*@param x2 下顶x坐标 @param y2 下顶y坐标*/
    int x2, y2;
    friend inline bool operator<(const Triangle& a, const Triangle& b) {
        return a.x1 < b.x1;
    }
} tri[MAXN];

int n, vis[MAXN], st, ed;
vector<int> G[MAXN], posX, chosen;
pair<double, double> seg[MAXN];

unordered_map<double, double> mp;
inline double f(double x) {
    if (mp.count(x)) return mp[x];
    int tot = 0;
    for (auto& i : chosen) {
        if (x < -EPS + tri[i].x1 || tri[i].x2 < -EPS + x) continue;
        seg[++tot].first = 1.0 * tri[i].y2;
        seg[tot].second = 1.0 * tri[i].y2 + tri[i].x2 - x;
    }
    sort(seg + 1, seg + tot + 1);
    double len = 0, l = seg[1].first;
    for (int i = 1; i <= tot; i++) {
        l = max(l, seg[i].first);
        if (l < seg[i].second - EPS) len += seg[i].second - l;
        l = max(l, seg[i].second);
    }
    return mp[x] = len;
}

inline double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (f(l) + f(mid) * 4 + f(r)) * (r - l) / 6;
}

double integral(double l, double r, double eps, double i) {
    double mid = (l + r) / 2;
    double iL = simpson(l, mid), iR = simpson(mid, r);
    if (fabs(iL + iR - i) <= eps * 15) return iL + iR + (iL + iR - i) / 15;
    return integral(l, mid, eps / 2, iL) + integral(mid, r, eps / 2, iR);
}

inline void init(double res = 0) {
    sort(tri + 1, tri + n + 1);
    sort(posX.begin(), posX.end());
    auto edIt = unique(posX.begin(), posX.end());
    for (auto it = posX.begin() + 1; it != edIt; it++) {
        double l = *(it - 1), r = *(it);
        chosen.clear();
        for (int i = 1; i <= n; i++) {
            if ((tri[i].x1 <= l && l <= tri[i].x2) ||
                (tri[i].x1 <= r && r <= tri[i].x2)) {
                chosen.push_back(i);
            }
        }
        l += 2e-9, r -= 2e-9; //偏移边界
        res += integral(l, r, 1e-4, simpson(l, r));
    }
    cout << setprecision(1) << fixed << res << endl;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, x, y, m; i <= n; i++) {
        cin >> x >> y >> m;
        tri[i].x1 = x, tri[i].y1 = y + m;
        tri[i].x2 = x + m, tri[i].y2 = y;
        posX.push_back(x), posX.push_back(x + m);
    }
    init();
    return 0;
}