#include <bits/stdc++.h>
//nowcoder cutting game
using namespace std;

int n, m, sg[302][302];

inline int SG(int n, int m) {
    bool vis[302]; //!don't use global variable
    memset(vis, false, sizeof(vis));
    if (sg[n][m] != -1) return sg[n][m];
    for (int i = 2; i <= n - i; i++) vis[SG(i, m) xor SG(n - i, m)] = 1;
    for (int i = 2; i <= m - i; i++) vis[SG(n, i) xor SG(n, m - i)] = 1;
    int mex = 0;
    while (vis[mex]) ++mex;
    return sg[n][m] = mex;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    memset(sg, -1, sizeof(sg));
    sg[2][2] = sg[2][3] = sg[3][2] = 0;
    //先剪出 1 * 1获胜 3 * 2 2 * 3 2 * 2 为必败状态
    while (cin >> n >> m) {
        SG(n, m) ? cout << "WIN\n" : cout << "LOSE\n";
    }
    return 0;
}