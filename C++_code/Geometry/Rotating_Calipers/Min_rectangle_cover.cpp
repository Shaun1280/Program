#include <bits/stdc++.h>
#define PI acos(-1)
//P3187 [HNOI2007]最小矩形覆盖
using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr long double EPS = 1e-10;

struct Vec2 {
    Vec2() = default;
    Vec2(long double _x, long double _y) : x(_x), y(_y) {}

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
    friend inline long double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;  //×
    }
    /*@return 向量与数乘后的向量*/
    friend inline Vec2 operator*(const Vec2& a, long double num) {
        return Vec2(a.x * num, a.y * num);
    }
    /*@param a 2D vector @return norm of the vector*/
    friend inline long double norm(const Vec2& a) {
        return sqrt(a.x * a.x + a.y * a.y);
    }
    /*@param a 2D vector @return square norm of the vector*/
    friend inline long double normSquare(const Vec2& a) {
        return a.x * a.x + a.y * a.y;
    }
    /*@return dot product of two vectors*/
    friend inline long double dot(const Vec2& a, const Vec2& b) {
        return a.x * b.x + a.y * b.y;
    }
    long double x = 0, y = 0;
} vec[MAXN], ans[4];

/*@return intersect point of two Seg*/
inline Vec2 intersect(const Vec2& s1, const Vec2& t1, const Vec2& s2,
                      const Vec2& t2) {
    long double ratio = ((s1 - s2) * (t2 - s2)) / ((t2 - s2) * (t1 - s1));
    return s1 + (t1 - s1) * ratio;
}

int cnt;
int stk[MAXN], used[MAXN], top;
//multi test case: remember to memset used[]
inline void convex() {  //求凸包
    sort(vec + 1, vec + cnt + 1);
    top = 0, stk[++top] = 1;
    for (int i = 2; i <= cnt; i++) {  //下凸壳
        while (top > 1 &&
               (vec[stk[top]] - vec[stk[top - 1]]) * (vec[i] - vec[stk[top]]) <=
                   EPS)
            used[stk[top--]] = false;
        used[i] = true, stk[++top] = i;
    }
    long double tmp = top;
    for (int i = cnt - 1; i > 0; i--) {  //上凸壳
        if (!used[i]) {
            while (top > tmp && (vec[stk[top]] - vec[stk[top - 1]]) *
                                        (vec[i] - vec[stk[top]]) <=
                                    EPS)
                used[stk[top--]] = false;
            used[i] = true, stk[++top] = i;
        }
    }
}

inline void rotatingCalipers(long double res = 1e18) { //旋转卡壳
    convex();
    int up = 1, left = 3, right = 1;
    for (int i = 1; i < top; i++) {
        auto s = vec[stk[i]], t = vec[stk[i + 1]];
        while (true) {  //寻找对踵点 two polong doubleers
            auto x1 = vec[stk[up]], x2 = vec[stk[up + 1]];
            long double s1 = abs((s - x1) * (t - x1));
            long double s2 = abs((s - x2) * (t - x2));
            if (s1 < s2 + EPS) up = up % (top - 1) + 1;  // h1 <= h2
            else break;
        }
        while (true) {  //右边最远的点
            auto x1 = vec[stk[right]], x2 = vec[stk[right + 1]];
            long double s1 = dot(x1 - s, t - s);
            long double s2 = dot(x2 - s, t - s);
            if (s1 < s2 + EPS) right = right % (top - 1) + 1;  // r1 <= r2
            else break;
        }
        while (true) {  //左边最远的点
            auto x1 = vec[stk[left]], x2 = vec[stk[left + 1]];
            long double s1 = dot(x1 - s, t - s);
            long double s2 = dot(x2 - s, t - s);
            if (s1 > EPS) left = left % (top - 1) + 1;
            else if (s2 < s1 + EPS) left = left % (top - 1) + 1;  // l2 <= l1
            else break;
        }
        long double theta = atan2(t.y - s.y, t.x - s.x);
        auto p1 = intersect( //直线相交求顶点
            s, t, vec[stk[left]],
            vec[stk[left]] + Vec2(cos(theta + PI / 2), sin(theta + PI / 2)));
        auto p2 = intersect( //直线相交求顶点
            s, t, vec[stk[right]],
            vec[stk[right]] + Vec2(cos(theta + PI / 2), sin(theta + PI / 2)));
        auto p3 = intersect( //直线相交求顶点
            vec[stk[up]], vec[stk[up]] + Vec2(cos(theta), sin(theta)),
            vec[stk[right]],
            vec[stk[right]] + Vec2(cos(theta + PI / 2), sin(theta + PI / 2)));
        auto p4 = intersect( //直线相交求顶点
            vec[stk[up]], vec[stk[up]] + Vec2(cos(theta), sin(theta)),
            vec[stk[left]],
            vec[stk[left]] + Vec2(cos(theta + PI / 2), sin(theta + PI / 2)));
        long double area = (p3 - p2) * (p1 - p2);
        if (area < res - EPS) { // area < res
            res = area;
            ans[0] = p1, ans[1] = p2, ans[2] = p3, ans[3] = p4;
        }
    }
    cout << res << endl;
}

inline void print() {
    int st;
    long double minY = 1e18, minX = 1e18;
    for (int i = 0; i < 4; i++) {
        if (ans[i].y < minY - EPS) {
            st = i, minY = ans[i].y, minX = ans[i].y;
        } else if (abs(ans[i].y - minY) < EPS) { //相等
            if (ans[i].x < minX - EPS) { //选x小的
                st = i, minY = ans[i].y, minX = ans[i].x;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        double x = ans[(st + i) % 4].x, y = ans[(st + i) % 4].y;
        if (abs(x) < EPS) x = .0;
        if (abs(y) < EPS) y = .0;
        cout << x << " " << y << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(5) << fixed;
    cin >> cnt;
    for (int i = 1; i <= cnt; i++) cin >> vec[i].x >> vec[i].y;
    rotatingCalipers(); //旋转卡壳求出矩形
    print(); //输出
    return 0;
}