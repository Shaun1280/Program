#include <bits/stdc++.h>
#define PI acos(-1)
//https://www.luogu.com.cn/problem/P4166 P4166 [SCOI2007]最大土地面积
using namespace std;

constexpr int MAXN = 3e3 + 3;

struct Vec2 {
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {}

    friend inline bool operator<(const Vec2& a, const Vec2& b) {
        return fabs(a.x - b.x) < 1e-8 ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    friend inline double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //×
    }
    double x = 0, y = 0;
} vec[MAXN], cov[MAXN];
int n, top, Up;

inline void convex() {
    top = 0, Up = 0;
    sort(vec + 1, vec + n + 1);
    for (int i = 1; i <= n; i++) {  //下凸壳
        while (top > 1 && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) < 1e-8)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
    Up = top;                          //上凸壳起点
    for (int i = n - 1; i > 0; i--) {  //上凸壳
        while (top > Up && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) < 1e-8)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
}

inline double calc(double res = .0) {
    if (top <= 3) return 0.0; //凸包只有2个点
    if (top == 4) ; //凸包只有3个点
    for (int i = 1; i < top; i++) {
        int up = (i + 2) % (top - 1) == 0 ? (i + 2) : (i + 2) % (top - 1);
        int down = i;
        for (int j = i + 2; j < i + top - 2; j++) {
            auto s = cov[i], t = cov[j % (top - 1) == 0 ? j : j % (top - 1)];
            while (true) {
                auto s1 = fabs((t - cov[up]) * (s - cov[up]));
                auto s2 = fabs((t - cov[up + 1]) * (s - cov[up + 1]));
                if (s1 < s2 + 1e-8) up = up % (top - 1) + 1;
                else break;
            }
            while (true) {
                auto s1 = fabs((t - cov[down]) * (s - cov[down]));
                auto s2 = fabs((t - cov[down + 1]) * (s - cov[down + 1]));
                if (s1 < s2 + 1e-8) down = down % (top - 1) + 1;
                else break;
            }
            res = max(res, fabs((cov[up]- s) * (cov[up] - t)) +
                               fabs((cov[down] - s) * (cov[down] - t)));
        }
    }
    return res / 2;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> vec[i].x >> vec[i].y;
    convex();
    cout << setprecision(3) << fixed << calc() << endl;;
    return 0;
}