#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc223/tasks/abc223_g
// G - Vertex Deletion
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n;
bool dp[MAXN], f[MAXN];
int cnt[MAXN][2]; // 0 white && 1 black
vector<int> g[MAXN];

void DP(int cur, int fa) {
    for (auto& to : g[cur]) {
        if (to == fa) continue;
        DP(to, cur);
        dp[cur] |= (!dp[to]);
        cnt[cur][dp[to]]++;
    }
}

void dfs(int cur, int fa) {
    for (auto& to : g[cur]) {
        if (to == fa) continue;
        cnt[cur][dp[to]]--;

        bool colorCur;
        if (cnt[cur][0]) colorCur = true;
        else colorCur = false;

        f[to] = (dp[to] | (!colorCur));
        cnt[to][colorCur]++;

        dfs(to, cur);

        cnt[cur][dp[to]]++;
    }
}

signed main() {
    boost;
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    DP(1, 0);
    f[1] = dp[1], dfs(1, 0);
    int ans(0);
    for (int i = 1; i <= n; i++) ans += (!f[i]);
    cout << ans << "\n";
    return 0;
}