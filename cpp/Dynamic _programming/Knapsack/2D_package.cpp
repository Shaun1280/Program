#include <bits/stdc++.h>
// find min cnt such that suma >= x && sumb >= y
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 303, MOD = 1e9 + 7;

int n, X, Y, a[MAXN], b[MAXN], dp[2][MAXN][MAXN];

template<typename T>
void chmin(T& a, T b) { if (a > b) a = b; }

int main() {
    boost;
    cin >> n >> X >> Y;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        memset(dp[i & 1], 0x3f, sizeof(dp[i & 1]));
        dp[(i & 1) ^ 1][0][0] = 0;
        for (int x = X; x >= 0; x--)
            for (int y = Y; y >= 0; y--) {
                chmin(dp[i & 1][x][y], dp[(i & 1) ^ 1][x][y]);
                chmin(dp[i & 1][min(x + a[i], X)][min(y + b[i], Y)], dp[(i & 1) ^ 1][x][y] + 1);
            }
    }
    if (dp[n & 1][X][Y] == 0x3f3f3f3f) cout << -1 << "\n";
    else cout << dp[n & 1][X][Y] << "\n";
    return 0;
}