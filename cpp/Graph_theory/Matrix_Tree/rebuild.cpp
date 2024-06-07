#include <bits/stdc++.h>
//P3317 [SDOI2014]重建 https://www.luogu.com.cn/problem/P3317
using namespace std;
using LL = long long;
//变元矩阵树，G[i][i]为边权和，G[i][j]为i j间边权和
int n;
double ans(1), eps = 1e-8;

double G[55][55], p[55][55];
inline double Gauss() {
    double ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(G[i][i]) < eps) swap(G[i], G[j]), ans = -ans;
            else break;
        }
        for (int j = i + 1; j < n; j++) {
            if (fabs(G[j][i]) < eps) continue;
            double tmp = G[j][i] / G[i][i];
            for (int k = i; k < n; k++)
                G[j][k] -= tmp * G[i][k];
        }
        ans = ans * G[i][i];
    }
    return ans;
}

inline void add(int u, int v, double val) {
    G[u][u] += val, G[v][v] += val;
    G[u][v] -= val, G[v][u] -= val;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout << setprecision(4) << fixed;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> p[i][j];
            if (i >= j) continue;
            double tmp = fabs(1.0 - p[i][j]) < eps ? eps : fabs(1.0 - p[i][j]);
            ans *= tmp, p[i][j] /= tmp;
            add(i, j, p[i][j]);
        }
    cout << ans * fabs(Gauss()) << endl;
    return 0;
}