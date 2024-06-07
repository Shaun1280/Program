#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2419
//传递闭包
const int MAXN = 1e2 + 2;

using namespace std;

int n, m, f[MAXN][MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        f[u][v] = 1; //u 赢了 v
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) f[i][j] |= f[i][k] & f[k][j];
    int tot(0);
    for (int i = 1; i <= n; i++) {
        int st = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            st = st & (f[i][j] | f[j][i]);
        }
        tot += st;
    }
    cout << tot << endl; // 可以确定排名地奶牛数目
    return 0;
}