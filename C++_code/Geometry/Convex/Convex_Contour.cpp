#include <bits/stdc++.h>
// P3680 [CERC2016]凸轮廓线 Convex Contour
#define PI acos(-1)

using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr int M = 1e4;

struct Vec2 {
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {}

    friend inline bool operator<(const Vec2& a, const Vec2& b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    friend inline double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //×
    }
    double x = .0, y = .0;
} vec[MAXN], cov[MAXN];

int cnt;
int top(0), up;

inline double convex(double res = 0) {
    sort(vec + 1, vec + cnt + 1);
    for (int i = 1; i <= cnt; i++) {  //下凸壳
        while (top > 1 && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) <= 0)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
    up = top; //上凸壳起点
    for (int i = cnt - 1; i > 0; i--) {  //上凸壳
        while (top > up && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) <= 0)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
    for (int i = 1; i < top; i++) {  //凸包中的所有点
        Vec2 tmp = cov[i + 1] - cov[i];
        res += sqrt(pow(tmp.x, 2) + pow(tmp.y, 2));
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    double n, st(0);
    string s;
    cin >> n >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'S') {
            vec[++cnt] = Vec2(st, 0);
            vec[++cnt] = Vec2(st, 2);
            vec[++cnt] = Vec2(st + 2, 0);
            vec[++cnt] = Vec2(st + 2, 2);
        } else if (s[i] == 'T') {
            vec[++cnt] = Vec2(st, 0);
            vec[++cnt] = Vec2(st + 2, 0);
            vec[++cnt] = Vec2(st + 1, sqrt(3.0));
        } else {
            for (int j = 1; j <= M; j++) {
                double theta = PI * 2 * j / M;
                vec[++cnt] = Vec2(st + 1 + cos(theta), 1 + sin(theta));
            }
        }
        st += 2;
    }
    cout << setprecision(14) << fixed << convex() / 2 << endl;
    return 0;
}