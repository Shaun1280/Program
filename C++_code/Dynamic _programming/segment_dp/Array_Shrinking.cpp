#include<bits/stdc++.h>
//https://codeforces.ml/contest/1312/problem/E
#define boost std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

using namespace std;
using LL = long long;

constexpr int MAXN = 505;
constexpr LL M = 998244353;

int n, a[MAXN], dp[MAXN][MAXN], w[MAXN][MAXN];

template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}


int main() {
    boost;
    cin >> n;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) cin >> a[i], dp[i][i] = 1, w[i][i] = a[i];
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int mid = l; mid < r; mid++) {
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r]);
                if (dp[l][mid] == 1 && dp[mid + 1][r] == 1 && w[l][mid] == w[mid + 1][r])
                    dp[l][r] = 1, w[l][r] = w[l][mid] + 1;
            }
        }
    cout << dp[1][n] << endl;
    return 0;
}