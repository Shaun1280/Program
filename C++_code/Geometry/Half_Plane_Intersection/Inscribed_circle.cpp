#include <bits/stdc++.h>
#define PI acos(-1)
//UVA1396 Most Distant Point from the Sea https://www.luogu.com.cn/problem/UVA1396
using namespace std;
//求多边形最大内切圆半径 二分 + 半平面交
constexpr long double EPS = 1e-11;
constexpr int MAXN = 300;

struct Vec2 {  //点向量类
    Vec2() = default;
    Vec2(long double _x, long double _y) : x(_x), y(_y) {}
    /*Vec2 vector a - Vec2 vector b @return Vec2(x, y)*/
    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }
    /*Vec2 vector a + Vec2 vector b @return Vec2(x, y)*/
    friend inline Vec2 operator+(const Vec2& a, const Vec2& b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }
    /*cross product of two Vec2 vector (starting point is zero)*/
    friend inline long double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;
    }
    /*Vec2 * num operation @return Vec2(x, y)*/
    friend inline Vec2 operator*(const Vec2& a, long double num) {
        return Vec2(a.x * num, a.y * num);
    }
    /*input coordinate of Vec2 through istream*/
    inline friend istream& operator>>(istream& is, Vec2& p) {
        is >> p.x >> p.y;
        return is;
    }
    /*@param x x坐标 @param y y坐标*/
    long double x = 0, y = 0;
} vertex[MAXN], its[MAXN]/*intersected points*/;

struct Seg {  //线段类 起点s, 终点t
    Seg() = default;
    Seg(Vec2 _s, Vec2 _t) : s(_s), t(_t) { theta = atan2((t - s).y, (t - s).x); }
    /*comparison of two Seg @return bool*/
    friend inline bool operator<(const Seg& a, const Seg& b) {//比较极角
        // theta1 != theta2 按theta排序
        if (abs(a.theta - b.theta) > EPS) return a.theta < b.theta;
        // theta1 == theta2 判断向量a在b的哪边，令最靠左的排在最左边
        return (b.s - a.s) * (b.t - a.s) > EPS;
    }
    /*intersection of two Seg @return Vec2(x, y)*/
    inline friend Vec2 intersect(const Seg& a, const Seg& b) {
        long double ratio = ((b.t - b.s) * (a.s - b.s)) / ((a.t - a.s) * (b.t - b.s));
        return a.s + (a.t - a.s) * ratio;
    }
    /*@param s 起点 @param t 终点*/
    Vec2 s, t;
    /*@param theta 极角*/
    long double theta = 1e9;
} seg[MAXN], sg[MAXN], q[MAXN]/*deque 队列中存放线段*/;
int n, tot;
/*求向量左侧的半平面交 队列范围[l, r]*/
inline bool halfPlaneIntersection() {
    sort(sg + 1, sg + tot + 1);
    int l = 0, r = 0;
    for (int i = 1; i <= tot; i++) {
        if (abs(sg[i].theta - sg[i - 1].theta) > EPS) {
            while (r - l > 1 && (sg[i].t - its[r]) * (sg[i].s - its[r]) > EPS)
                --r;
            while (r - l > 1 && (sg[i].t - its[l + 2]) * (sg[i].s - its[l + 2]) > EPS)
                ++l;
            q[++r] = sg[i];
            if (r - l > 1) its[r] = intersect(q[r], q[r - 1]); //求新交点
        }
    }
    while (r - l > 1 && (q[l + 1].t - its[r]) * (q[l + 1].s - its[r]) > EPS)
        --r; //删除多余元素
    its[r + 1] = intersect(q[l + 1], q[r]), ++r; //终点线段与起点线段相交

    long double ans(0);
    for (int i = l + 2; i < r; i++) { // l + 2 是起始交点 三角剖分求面积
        ans += (its[i] * its[i + 1]) / 2;
    }
    ans += (its[r] * its[l + 2]) / 2;
    //cout << setprecision(3) << fixed << ans << endl;
    return ans > EPS;
}

inline void translate(long double mid) { //平移 mid
    for (int i = 1; i <= tot; i++) {
        long double theta = seg[i].theta + PI / 2;
        long double deltaX = mid * cos(theta);
        long double deltaY = mid * sin(theta);
        auto delta = Vec2(deltaX, deltaY);
        sg[i] = Seg(seg[i].s + delta, seg[i].t + delta);
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    while (cin >> n && n) {
        tot = 0;
        for (int i = 1; i <= n; i++) cin >> vertex[i];
        for (int i = 1; i <= n; i++)
            seg[++tot] = Seg(vertex[i], vertex[i % n + 1]);
        long double l = 0, r = 1e5;
        while (l < r - EPS) {
            long double mid = (l + r) / 2;
            translate(mid);
            if (halfPlaneIntersection()) l = mid;
            else r = mid;
        }
        cout << setprecision(8) << fixed << l << endl;
    }
    return 0;
}