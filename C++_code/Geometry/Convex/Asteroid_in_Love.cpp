#include <bits/stdc++.h>
//http://acm.hdu.edu.cn/showproblem.php?pid=6830
using namespace std;
using LL = long long;
//Asteroid in Love 凸包 + 三分法
constexpr LL MAXN = 3e3 + 3;

LL tc, n, top[3], up[3], cnt[3], ans;

struct Vec2 {
    Vec2() = default;
    Vec2(LL _x, LL _y) : x(_x), y(_y) {}

    friend inline Vec2 intersect(const Vec2&, const Vec2&, const Vec2&, const Vec2&);

    friend inline bool operator<(const Vec2& a, const Vec2& b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    friend inline Vec2 operator+(const Vec2& a, const Vec2& b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }
    /*@return cross product of two Vec2*/
    friend inline LL operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //×
    }
    /*@return 向量与数乘后的向量*/
    friend inline Vec2 operator*(const Vec2& a, LL num) {
        return Vec2(a.x * num, a.y * num);
    }
    /*@param a 2D vector @return norm of the vector*/
    friend inline LL norm(const Vec2& a) {
        return sqrt(a.x * a.x + a.y * a.y);
    }
    /*@param a 2D vector @return square norm of the vector*/
    friend inline LL normSquare(const Vec2& a) {
        return a.x * a.x + a.y * a.y;
    }

    LL x = 0, y = 0;
} vec[3][MAXN], cov[3][MAXN]/*三类凸包*/;

inline void convex(int x) { //x表示类型
    top[x] = up[x] = 0;
    sort(vec[x] + 1, vec[x] + cnt[x] + 1);
    LL& tp = top[x], &tmp = up[x];
    for (int i = 1; i <= cnt[x]; i++) {  //下凸壳
        while (tp > 1 && (cov[x][tp] - cov[x][tp - 1]) * (vec[x][i] - cov[x][tp]) <= 0)
            cov[x][tp--] = Vec2(0, 0);
        cov[x][++tp] = vec[x][i];
    }
    tmp = tp; //上凸壳起点
    for (int i = cnt[x] - 1; i > 0; i--) {  //上凸壳
        while (tp > tmp && (cov[x][tp] - cov[x][tp - 1]) * (vec[x][i] - cov[x][tp]) <= 0)
            cov[x][tp--] = Vec2(0, 0);
        cov[x][++tp] = vec[x][i];
    }
}

inline LL trisection(const Vec2& a, const Vec2& b, int x, LL res = 0) {
    LL l = 1, r = up[x]; //三分法
    while (r - l >= 3) { //单峰
        LL lmid = (l + l + r) / 3;
        LL rmid = (l + r + r) / 3;
        LL ls = (cov[x][lmid] - a) * (cov[x][lmid] - b);
        LL rs = (cov[x][rmid] - a) * (cov[x][rmid] - b);
        if (ls > rs) r = rmid;
        else l = lmid;
    }
    for (int i = l; i <= r; i++) res = max(res, abs((cov[x][i] - a) * (cov[x][i] - b)));

    l = 1, r = up[x];
    while (r - l >= 3) { //单谷
        LL lmid = (l + l + r) / 3;
        LL rmid = (l + r + r) / 3;
        LL ls = (cov[x][lmid] - a) * (cov[x][lmid] - b);
        LL rs = (cov[x][rmid] - a) * (cov[x][rmid] - b);
        if (ls < rs) r = rmid;
        else l = lmid;
    }
    for (int i = l; i <= r; i++) res = max(res, abs((cov[x][i] - a) * (cov[x][i] - b)));

    l = up[x], r = top[x];
    while (r - l >= 3) { //单峰
        LL lmid = (l + l + r) / 3;
        LL rmid = (l + r + r) / 3;
        LL ls = (cov[x][lmid] - a) * (cov[x][lmid] - b);
        LL rs = (cov[x][rmid] - a) * (cov[x][rmid] - b);
        if (ls > rs) r = rmid;
        else l = lmid;
    }
    for (int i = l; i <= r; i++) res = max(res, abs((cov[x][i] - a) * (cov[x][i] - b)));

    l = up[x], r = top[x];
    while (r - l >= 3) { //单谷
        LL lmid = (l + l + r) / 3;
        LL rmid = (l + r + r) / 3;
        LL ls = (cov[x][lmid] - a) * (cov[x][lmid] - b);
        LL rs = (cov[x][rmid] - a) * (cov[x][rmid] - b);
        if (ls < rs) r = rmid;
        else l = lmid;
    }
    for (int i = l; i <= r; i++) res = max(res, abs((cov[x][i] - a) * (cov[x][i] - b)));
    return res;
}

int main () {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(1) << fixed;
    cin >> tc;
    while (tc--) {
        cin >> n;
        ans = 0;
        memset(cnt, 0, sizeof(cnt));
        for (LL i = 1, x, y, type; i <= n; i++) {
            cin >> x >> y >> type;
            vec[type][++cnt[type]] = Vec2(x, y);
        }
        for (int type = 0; type < 3; type++) convex(type);
        for (int x = 0; x < 1; x++) //枚举星星类型
            for (int y = x + 1; y <= 2; y++)
                 for (int i = 1; i <= cnt[x]; i++)
                    for (int j = 1; j <= cnt[y]; j++)
                        ans = max(ans, trisection(vec[x][i], vec[y][j], 3 - x - y));
        long double res = ans; //注意精度
        cout << res / 2 << endl;
    }
    return 0;
}