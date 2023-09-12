#include <bits/stdc++.h>
//P4207 [NOI2005]月下柠檬树 https://www.luogu.com.cn/problem/P4207
using namespace std;

constexpr int MAXN = 3e3 + 3;
constexpr double EPS = DBL_EPSILON;

int n;
double h[MAXN], sumH, alpha;

struct Circle {
    /*@param x x of center O @param y y of center O @param R radius*/
    double x, y, R;
    /*@param l 最左端 @param r 最右端*/
    double l, r;
} circle[MAXN];

struct Seg {
    double l, r;
    friend inline bool operator<(const Seg& a, const Seg& b) {
        return a.l < b.l - EPS;
    }
} seg[MAXN];

struct Trapezoid {      //梯形类
    double x1, y1; //右上顶点
    double x2, y2; //右下顶点
    double deltaX = 0, height = 0;
} trape[MAXN];

unordered_map<double, double> mp;
inline double f(double x) {  //算x处覆盖的线段总长
    if (mp.count(x)) return mp[x];
    int tot = 0;
    for (int i = 1; i <= n; i++) { //圆形
        double tmp = pow(circle[i].R, 2) - pow(x - circle[i].x, 2);
        if (tmp < EPS) continue;
        seg[++tot].l = circle[i].y - sqrt(tmp);
        seg[tot].r = circle[i].y + sqrt(tmp);
    }
    for (int i = 1; i <= n; i++) {  //梯形
        double l = min(trape[i].x1, trape[i].x2);
        double r = max(trape[i].x1, trape[i].x2);
        if (r < x + EPS) continue;
        if (x < l + EPS) {
            seg[++tot].l = trape[i].y2, seg[tot].r = trape[i].y1;
            continue;
        }
        double delta = trape[i].x2 - x;
        double ratio = abs(delta / trape[i].deltaX);
        if (trape[i].deltaX > EPS) {
            seg[++tot].r = trape[i].y2 + trape[i].height * ratio;
            seg[tot].l = trape[i].y2;
        } else if (trape[i].deltaX < EPS) {
            seg[++tot].l = trape[i].y2 + trape[i].height * ratio;
            seg[tot].r = trape[i].y1;
        }
    }
    sort(seg + 1, seg + tot + 1);
    double len = .0, l = seg[1].l;
    for (int i = 1; i <= tot; i++) {
        l = max(l, seg[i].l);
        if (l < seg[i].r - EPS) len += seg[i].r - l;
        l = max(l, seg[i].r);
    }
    return mp[x] = len;
}

inline double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (f(l) + f(mid) * 4 + f(r)) * (r - l) / 6;
}

double integral(double l, double r, double eps, double i) {
    double mid = (l + r) / 2;
    double iL = simpson(l, mid), iR = simpson(mid, r);
    if (fabs(iL + iR - i) <= eps * 15) return iL + iR + (iL + iR - i) / 15;
    return integral(l, mid, eps / 1.6, iL) + integral(mid, r, eps / 1.6, iR);
}

inline double calc() {  //计算面积并
    for (int i = 1; i <= n; i++) {
        double dis = circle[i + 1].y - circle[i].y;  //圆心距离
        if (dis < abs(circle[i].R - circle[i + 1].R) + EPS) continue;
        double theta = acos((circle[i].R - circle[i + 1].R) / dis);
        trape[i].x1 = circle[i + 1].R * sin(theta); //右上顶点
        trape[i].y1 = circle[i + 1].y + circle[i + 1].R * cos(theta);
        trape[i].x2 = circle[i].R * sin(theta); //右下顶点
        trape[i].y2 = circle[i].y + circle[i].R * cos(theta);
        trape[i].deltaX = trape[i].x2 - trape[i].x1; //
        trape[i].height = trape[i].y1 - trape[i].y2; //高度
    }
    double l = circle[1].l, r = circle[1].r;
    for (int i = 2; i <= n; i++)
        l = min(l, circle[i].l), r = max(r, circle[i].r);
    return integral(0, r, 5e-4, simpson(l, r)) * 2; //对称性 对以边积分
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(2) << fixed;
    cin >> n >> alpha;
    for (int i = 0; i <= n; i++) cin >> h[i];
    sumH = h[0];
    for (int i = 1; i <= n; i++) {
        cin >> circle[i].R;
        circle[i].x = 0, circle[i].y = sumH / tan(alpha);
        circle[i].l = -circle[i].R, circle[i].r = circle[i].R;
        sumH += h[i];
    }
    circle[n + 1].x = 0, circle[n + 1].y = sumH / tan(alpha);
    circle[n + 1].l = 0, circle[n + 1].r = 0;  //顶点
    cout << calc() << endl;
    return 0;
}