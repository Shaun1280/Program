#include <bits/stdc++.h>
//https://atcoder.jp/contests/abc184/tasks/abc184_d
using namespace std;

constexpr int MAXN = 101, MOD = 1e9 + 7;

int a, b, c;
double dp[MAXN][MAXN][MAXN]; //dp[i][j][k]表示从100开始，取走coin后数目为i, j, k的期望

int main() {
    cin >> a >> b >> c;
    for (int i = 99; i >= a; i--)
        for (int j = 99; j >= b; j--)
            for (int k = 99; k >= c; k--) {
                int sum = i + j + k; 
                dp[i][j][k] += (dp[i + 1][j][k] + 1) * 1.0 * i / sum; //期望可加
                dp[i][j][k] += (dp[i][j + 1][k] + 1) * 1.0 * j / sum;
                dp[i][j][k] += (dp[i][j][k + 1] + 1) * 1.0 * k / sum;
            }
    cout << setprecision(12) << fixed << dp[a][b][c] << endl;
    return 0;
}