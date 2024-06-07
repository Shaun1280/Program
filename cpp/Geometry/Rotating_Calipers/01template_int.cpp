#include <bits/stdc++.h>
#define PI acos(-1)
//P1452 [USACO03FALL]Beauty Contest G /【模板】旋转卡壳
using namespace std;
using LL = long long;
//整数旋转卡壳
constexpr int MAXN = 2e5 + 5;

struct Vec2 {
    Vec2() = default;
    Vec2(LL _x, LL _y) : x(_x), y(_y) {}

    friend inline bool operator<(const Vec2& a, const Vec2& b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }
    /*@return cross product of two Vec2*/
    friend inline LL operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //×
    }
    /*@param a 2D vector @return square norm of the vector*/
    friend inline LL normSquare(const Vec2& a) {
        return a.x * a.x + a.y * a.y;
    }
    LL x = 0, y = 0;
} vec[MAXN], cov[MAXN];

LL n, top;

inline void convex() {
    top = 0;
    sort(vec + 1, vec + n + 1);
    for (int i = 1; i <= n; i++) {  //下凸壳
        while (top > 1 && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) <= 0)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
    int up = top; //上凸壳起点
    for (int i = n - 1; i > 0; i--) {  //上凸壳
        while (top > up && (cov[top] - cov[top - 1]) * (vec[i] - cov[top]) <= 0)
            cov[top--] = Vec2(0, 0);
        cov[++top] = vec[i];
    }
}

inline LL rotatingCalipers(LL res = 0) { //旋转卡壳
    convex();
    int up = 1, left = 1, right = 1;
    if (top == 3) return normSquare(cov[1] - cov[2]);
    for (int i = 1; i < top; i++) {
        while (true) { //寻找对踵点 two polong doubleers
            auto s = cov[i], t = cov[i + 1];
            auto x1 = cov[up], x2 = cov[up + 1];
            LL s1 = abs((s - x1) * (t - x1));
            LL s2 = abs((s - x2) * (t - x2));
            if (s1 <= s2) up = up % (top - 1) + 1; //h1 <= h2
            else break;
        }
        res = max(res, normSquare(cov[i] - cov[up]));
        res = max(res, normSquare(cov[i + 1] - cov[up]));
    }   
    return res;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (LL i = 1; i <= n; i++)
        cin >> vec[i].x >> vec[i].y;
    cout << rotatingCalipers() << endl;
    return 0;
}