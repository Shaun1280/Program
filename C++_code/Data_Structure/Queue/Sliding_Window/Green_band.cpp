#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2219 
// P2219 [HAOI2007]修筑绿化带
// 每个 A * B 的矩形中有 C * D 的花坛，花坛必须被绿化带围绕
// 求绿化带肥沃度最大值
// 二维滑动窗口维护二维前缀和最值
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e3 + 3, MOD = 1e9 + 7;

int n, m, c, d, a, b;
long long pre[MAXN][MAXN], mn[MAXN][MAXN];

long long sum(int i, int j, int h, int w) { // 高 h 宽 w
    return pre[i][j] - (pre[i - h][j] + pre[i][j - w] - pre[i - h][j - w]);
}

int main() {
    boost;
    cin >> n >> m >> a >> b >> c >> d;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, tmp; j <= m; j++) {
            cin >> tmp;
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + tmp;
        }
    }
    deque<int> qMin;
    for (int i = c; i <= n; i++) {
        qMin.clear();
        for (int j = d; j <= m; j++) {
            while (!qMin.empty() && j - qMin.front() + 1 > b - d - 1) qMin.pop_front();
            while (!qMin.empty() && sum(i, j, c, d) <= sum(i, qMin.back(), c, d)) qMin.pop_back();
            qMin.push_back(j);
            if (j >= b - 1) mn[i][j] = sum(i, qMin.front(), c, d);
        }
    }
    long long res = LONG_LONG_MIN;
    for (int j = b; j <= m; j++) {
        qMin.clear();
        for (int i = c + 1; i <= n - 1; i++) {
            while (!qMin.empty() && i - qMin.front() + 1 > a - c - 1) qMin.pop_front();
            while (!qMin.empty() && mn[i][j - 1] <= mn[qMin.back()][j - 1]) qMin.pop_back();
            qMin.push_back(i);
            if (i + 1 >= a) {
                res = max(res, sum(i + 1, j, a, b) - mn[qMin.front()][j - 1]);
            }
        }
    }
    cout << res << "\n";
    return 0;
}