#include <bits/stdc++.h>
// [JSOI2007]合金 https://www.luogu.com.cn/problem/P4049
using namespace std;

constexpr int MAXN = 505;
constexpr double EPSILON = 1e-15;

struct Vec2 {
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {} //构造函数

    friend inline double operator* /*×*/(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //向量叉乘
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);  //向量相减
    }

    friend inline double dotProduct(const Vec2& a, const Vec2& b) {
        return a.x * b.x + a.y * b.y; //向量点乘
    }

    double x = .0, y = .0;
} mat[MAXN], pro[MAXN];  // material and product

int n, m, ans(0x3f3f3f3f), dis[MAXN][MAXN];

inline void init() {
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) { //求凸包 连边
            bool connect = true;
            for (int k = 1; k <= n; k++) {
                double cross = (mat[j] - mat[i]) * (pro[k] - mat[i]);
                double dot = dotProduct(mat[j] - pro[k], mat[i] - pro[k]);
                if (cross < -EPSILON || (abs(cross) < EPSILON && dot > EPSILON))
                    connect = false;
            } //所有产品对应的点都应在两材料对应点的左侧(逆时针方向看)，否则不连边
            if (connect) dis[i][j] = 1;
        }
}

inline void floyed() {
    for (int k = 1; k <= m; k++) //floyed求最小换
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
    for (int i = 1; i <= m; i++) ans = min(ans, dis[i][i]);
    cout << (ans == 0x3f3f3f3f ? -1 : ans) << endl;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> m >> n;
    double a, b, c;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> c;
        mat[i] = Vec2(a, b);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a >> b >> c;
        pro[i] = Vec2(a, b);
    }
    init();
    floyed();
    return 0;
}