#include <bits/stdc++.h>
#define down 0.996
//UVA10228 A Star not a Tree?
//https://www.luogu.com.cn/problem/UVA10228
using namespace std;

int t, n, x[101], y[101];
double ansx, ansy, ans;

inline double calc(int curx, int cury) {
    double res(0);
    for (int i = 1; i <= n; i++)
        res += sqrt(pow(x[i] - curx,2) + pow(y[i] - cury,2));
    return res;
}

inline void SA() {
    double T = 3000;
    while (T > 1e-15) {
        int curx = ansx + (rand() * 2 - RAND_MAX) * T;
        int cury = ansy + (rand() * 2 - RAND_MAX) * T;
        double tmp = calc(curx, cury);
        double delta = tmp - ans;
        if (delta < 0) {
            ansx = curx, cury = ansy, ans = tmp;
        } else if (exp(-delta / T) * RAND_MAX > rand())
            ansx = curx, cury = ansy;
        T *= down;
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        if (tc > 1) cout << endl;
        time_t st = clock();
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> x[i] >> y[i], ansx += x[i], ansy += y[i];
        ansx /= n, ansy /= n;
        ans = calc(ansx, ansy);
        while ((1.0 * (clock() - st) / CLOCKS_PER_SEC) < (2.0 / t))
            SA();
        cout << setprecision(0) << fixed << ans << endl;
    }
    return 0;
}