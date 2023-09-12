#include <bits/stdc++.h>
//SP8073 CIRU - The area of the union of circles 圆面积并
using namespace std;

constexpr int MAXN = 1e3 + 3;
constexpr long double EPS = 1e-10;

int n, vis[MAXN];
vector<int> chosen, G[MAXN];

struct Circle {
    /*@param x x of center O @param y y of center O @param R radius*/
    long double x, y, R;
    /*@param l 最左端 @param r 最右端*/
    long double l, r;
    /*按左端点排序 相同则按右端点排序*/
    friend inline bool operator<(const Circle& a, const Circle& b) {
        return a.l < b.l - EPS;
    }
} circle[MAXN];

struct Seg {
    /*@param l 左端点 @param r 右端点*/
    long double l, r;
    /*按左端点排序 相同则按右端点排序*/
    friend inline bool operator<(const Seg& a, const Seg& b) {
         return a.l < b.l - EPS;
    }
} seg[MAXN];

unordered_map<double, double> mp;
inline long double f(long double x) { //算x处覆盖的线段总长
    int tot = 0;
    for (auto& i : chosen) {
        long double tmp = pow(circle[i].R, 2) - pow(x - circle[i].x, 2);
        if (tmp < EPS) continue;
        seg[++tot].l = circle[i].y - sqrt(tmp);
        seg[tot].r = circle[i].y + sqrt(tmp);
    }
    sort(seg + 1, seg + tot + 1);
    long double l = seg[1].l, len = .0;
    for (int i = 1; i <= tot; i++) {
        l = max(l, seg[i].l);
        if (l < seg[i].r - EPS) len += seg[i].r - l;
        l = max(l, seg[i].r);
    }
    return len;
}

inline long double simpson(long double l, long double r) {
    long double mid = (l + r) / 2;
    return (f(l) + f(mid) * 4 + f(r)) * (r - l) / 6;
}

long double integral(long double l, long double r, long double eps) {
    long double mid = (l + r) / 2;
    long double iL = simpson(l, mid), iR = simpson(mid, r);
    long double i = simpson(l ,r);
    if (fabs(iL + iR - i) < eps * 15) return iL + iR + (iL + iR - i) / 15;
    return integral(l, mid, eps / 1.5) + integral(mid, r, eps / 1.5);
}

inline void init() {
    for (int i = 1; i <= n; i++) { //circle已按l排序
        if (vis[i] || circle[i].R < EPS) { //半径为0跳过
            vis[i] = true; continue;
        }
        for (int j = i + 1; j <= n; j++) {
            if (vis[j] || circle[j].R < EPS) { //半径为0跳过
                vis[j] = true; continue;
            }
            long double tmp = pow(circle[i].x - circle[j].x, 2)
                            + pow(circle[i].y - circle[j].y, 2);
            if (tmp < pow(circle[i].R - circle[j].R, 2) + EPS) {//被包含
                vis[j] = true; continue; //包含关系不加边
            }
            if (tmp < pow(circle[i].R + circle[j].R, 2) + EPS)
                G[i].push_back(j), G[j].push_back(i); //i与j联通
        }
    }
}

inline void dfs(int cur, long double& r) { //处理连通块
    vis[cur] = true, chosen.push_back(cur);
    for (auto& to : G[cur]) {
        if (vis[to]) continue;
        dfs(to, r = max(r, circle[to].r)); //求最大右端点
    }
}

inline long double calc() { //计算面积并
    long double l, r, ans = .0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        chosen.clear();
        l = circle[i].l, r = circle[i].r;
        dfs(i, r); //处理连通块
        if (chosen.size() == 1) ans += acos(-1) * circle[i].R * circle[i].R;
        else ans += integral(l, r, 1e-5);
    }
    return ans;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(3) << fixed;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> circle[i].x >> circle[i].y >> circle[i].R;
        circle[i].l = circle[i].x - circle[i].R;
        circle[i].r = circle[i].x + circle[i].R;
    }
    sort(circle + 1, circle + n + 1);
    init();
    cout << calc();
    return 0;
}