#include <bits/stdc++.h>
#define PI acos(-1)

using namespace std;

constexpr int MAXN = 1e3 + 3;

int n, top, up; //n 顶点数 top 栈顶

struct Vec2 {
    Vec2() = default;
    Vec2(int _x, int _y) : x(_x), y(_y) {}

    friend inline bool operator<(const Vec2 &a, const Vec2 &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    friend inline int operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x; //叉乘
    }
    int x = 0, y = 0;
} vec[MAXN], cov[MAXN];

inline double convex(double res = 0) {
    top = 0, up = 0;
    sort(vec + 1, vec + n + 1);
    for (int i = 1; i <= n; i++) {  //下凸壳
        while (top > 1 && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) <= 0)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
    up = top; //上凸壳起点
    for (int i = n - 1; i > 0; i--) {  //上凸壳
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
    return 0;
}