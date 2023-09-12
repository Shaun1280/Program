#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4525 P4525 【模板】自适应辛普森法1
using namespace std;

long double a, b, c, d, L, R;

unordered_map<double, double> mp;
inline long double f(long double x) {
    return (c * x + d) / (a * x + b);
}

inline long double simpson(long double l, long double r) {
    double mid = (l + r) / 2;
    return (f(l) + f(mid) * 4 + f(r)) * (r - l) / 6;
}

long double integral(long double l, long double r, long double eps) {
    long double mid = (l + r) / 2;
    long double iL = simpson(l, mid), iR = simpson(mid, r);
    long double i = simpson(l ,r);
    if (fabs(iL + iR - i) <= eps * 15) return iL + iR + (iL + iR - i) / 15;
    return integral(l, mid, eps / 2) + integral(mid, r, eps / 2);
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(6) << fixed;
    cin >> a >> b >> c >> d >> L >> R;
    cout << integral(L, R, 1e-7) << endl;
    return 0;
}