#include <bits/stdc++.h>
#define PI acos(-1)
// P4196 [CQOI2006]凸多边形 /【模板】半平面交
using namespace std;

constexpr double EPS = 1e-8;
constexpr int MAXN = 1e5 + 5;

struct Vec2 {  //点向量类
    Vec2() = default;
    Vec2(double _x, double _y) : x(_x), y(_y) {}
    /*Vec2 vector a - Vec2 vector b @return Vec2(x, y)*/
    friend inline Vec2 operator-(const Vec2& a, const Vec2& b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }
    /*Vec2 vector a + Vec2 vector b @return Vec2(x, y)*/
    friend inline Vec2 operator+(const Vec2& a, const Vec2& b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }
    /*cross product of two Vec2 vector (starting point is zero)*/
    friend inline double operator*(const Vec2& a, const Vec2& b) {
        return a.x * b.y - a.y * b.x;
    }
    /*Vec2 * num operation @return Vec2(x, y)*/
    friend inline Vec2 operator*(const Vec2& a, double num) {
        return Vec2(a.x * num, a.y * num);
    }
    /*input coordinate of Vec2 through istream*/
    inline friend istream& operator>>(istream& is, Vec2& p) {
        is >> p.x >> p.y;
        return is;
    }
    /*@param x x坐标 @param y y坐标*/
    double x = 0, y = 0;
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
        double ratio = ((b.t - b.s) * (a.s - b.s)) / ((a.t - a.s) * (b.t - b.s));
        return a.s + (a.t - a.s) * ratio;
    }
    /*@param s 起点 @param t 终点*/
    Vec2 s, t;
    /*@param theta 极角*/
    double theta = 1e9;
} seg[MAXN], q[MAXN]/*deque 队列中存放线段*/;
int n, cntVer, tot;
/*求向量左侧的半平面交 队列范围(l, r]*/
inline void halfPlaneIntersection() {
    sort(seg + 1, seg + tot + 1);
    int l = 0, r = 0;
    for (int i = 1; i <= tot; i++) {
        if (abs(seg[i].theta - seg[i - 1].theta) > EPS) {
            while (r - l > 1 && (seg[i].t - its[r]) * (seg[i].s - its[r]) > EPS)
                --r;
            while (r - l > 1 && (seg[i].t - its[l + 2]) * (seg[i].s - its[l + 2]) > EPS)
                ++l;
            q[++r] = seg[i];
            if (r - l > 1) its[r] = intersect(q[r], q[r - 1]); //求新交点
        }
    }
    while (r - l > 1 && (q[l + 1].t - its[r]) * (q[l + 1].s - its[r]) > EPS)
        --r; //删除多余元素
    its[r + 1] = intersect(q[l + 1], q[r]), ++r; //终点线段与起点线段相交

    double ans(0);
    for (int i = l + 2; i < r; i++) { // l + 2 是起始交点 三角剖分求面积
        ans += (its[i] * its[i + 1]) / 2;
    }
    ans += (its[r] * its[l + 2]) / 2;
    cout << setprecision(3) << fixed << ans << endl;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cntVer;
        for (int j = 1; j <= cntVer; j++) cin >> vertex[j];
        for (int j = 1; j < cntVer; j++)
            seg[++tot] = Seg(vertex[j], vertex[j + 1]);
        seg[++tot] = Seg(vertex[cntVer], vertex[1]);
    }
    halfPlaneIntersection();
    return 0;
}