#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2216
// [HAOI2007]理想的正方形
// 有一个 a * b 的整数组成的矩阵，
// 现请你从中找出一个 n * n 的正方形区域，
// 使得该区域所有数中的最大值和最小值的差最小。
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e3 + 3, MOD = 1e9 + 7;

int a, b, n;
int mx[MAXN][MAXN], mn[MAXN][MAXN], c[MAXN];

int main() {
    boost;
    cin >> a >> b >> n;
    deque<int> qMax, qMin;
    for (int i = 1; i <= a; i++) {
        qMax.clear(), qMin.clear();
        for (int j = 1; j <= b; j++) {
            cin >> c[j];
            while (!qMax.empty() && j - qMax.front() + 1 > n) qMax.pop_front();
            while (!qMin.empty() && j - qMin.front() + 1 > n) qMin.pop_front();

            while (!qMax.empty() && c[j] >= c[qMax.back()]) qMax.pop_back();
            while (!qMin.empty() && c[j] <= c[qMin.back()]) qMin.pop_back();
            qMax.push_back(j), qMin.push_back(j);
            if (j >= n) mx[i][j] = c[qMax.front()], mn[i][j] = c[qMin.front()];
        }
    }
    int res = INT_MAX;
    for (int j = n; j <= b; j++) {
        qMax.clear(), qMin.clear();
        for (int i = 1; i <= a; i++) {
            while (!qMax.empty() && i - qMax.front() + 1 > n) qMax.pop_front();
            while (!qMin.empty() && i - qMin.front() + 1 > n) qMin.pop_front();

            while (!qMax.empty() && mx[i][j] >= mx[qMax.back()][j]) qMax.pop_back(); // mx 的 mx
            while (!qMin.empty() && mn[i][j] <= mn[qMin.back()][j]) qMin.pop_back(); // mn 的 mn
            qMax.push_back(i), qMin.push_back(i);
            if (i >= n) res = min(res, mx[qMax.front()][j] - mn[qMin.front()][j]);
        }
    }
    cout << res << "\n";
    return 0;
}