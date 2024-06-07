#include <bits/stdc++.h>
/*
AT681 数
找出所有≤N的正整数，其在十进制表示下数码和是D的倍数。答案模1,000,000,007后输出。
数位dp
*/
const int MAXK = 1e2 + 2;
const int MAXN = 1e4 + 4;
typedef long long LL;
const LL MOD = 1e9 + 7;
using namespace std;
LL dp[MAXN][10][MAXK], ans; /*位数为i 最高位为j 余数为k*/
int D, n, digit[MAXN];
string N;
inline void calcuFromHighestDigit() {
    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= 9; j++) ans = (ans + dp[i][j][0]) % MOD;
    //位数为i(i < n)所有符合条件的数
    for (int i = digit[n] - 1; i >= 1; i--) ans = (ans + dp[n][i][0]) % MOD;
    /*处理最高位比N小的数*/
    int prefixSum = digit[n] % D;
    /*处理最高位和N相同的数*/
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j < digit[i]; j++) {
            ans = (ans + dp[i][j][(D - prefixSum) % D]) % MOD;
        }
        prefixSum = (prefixSum + digit[i]) % D;
    }
    if (prefixSum % D == 0) ans++;
    cout << ans << endl;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> D >> N;
    n = (int)N.size();
    for (int i = 0; i < n; i++) digit[i + 1] = N[n - i - 1] - 48;
    /*低位到高位*/
    for (int i = 0; i < 10; i++) dp[1][i][i % D] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = (i == n ? 1 : 0); j < 10; j++)
            for (int k = 0; k < D; k++) {  //上一位余数为k
                int remainder = (j + k) % D;
                for (int pre = 0; pre < 10; pre++)
                    dp[i][j][remainder] =
                        (dp[i][j][remainder] + dp[i - 1][pre][k]) % MOD;
            }
    calcuFromHighestDigit();
    return 0;
}