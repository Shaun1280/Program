#include <bits/stdc++.h>
//https://atcoder.jp/contests/abc187/tasks/abc187_f
using namespace std;
//Find the minimum possible number of connected components in the graph after 
//removing zero or more edges so that the following condition will be satisfied:
#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 3e5 + 5, MOD = 1e9 + 7, INF = 0x3f3f3f3f;

int n, m;
//Let dp[mask] deonte the minimum number of components
//for mask subset of nodes if they are forming valid clique components.
int main() {
    boost;
    cin >> n >> m;
    vector<int> g(n);
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b, a--, b--;
        g[a] |= 1 << b;
        g[b] |= 1 << a;
    }
    vector<int> dp(1 << n, INF);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 1 << n; j++) //(j | 1<< i) is a valid component bitmask
            if (dp[j] == 1 && (g[i] & j) == j) dp[j | 1 << i] = 1;
    for (int i = 1; i < 1 << n; i++)
        for (int j = i - 1; j &= i; j--) //enum subset Σ2^i = 3^n
            dp[i] = min(dp[i], dp[i ^ j] + dp[j]);
    cout << dp.back() << endl;
    return 0;
}