#include <bits/stdc++.h>
// /https://atcoder.jp/contests/abc190/tasks/abc190_e
using namespace std;
// E - Magical Ornament 
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n, m, k, f[18][18]; //f[i][j] is the number of nodes between (c[i], c[j]]
int dp[1 << 17][18]; //dp[i][j] state i, the last node visited is j
vector<int> g[MAXN];
array<int, 18> c;
array<int, MAXN> vis, dis;

void bfs(int i) {
    for (int i = 1; i <= n; i++) dis[i] = 0x3f3f3f3f, vis[i] = 0;
    queue<int> q;
    q.push(c[i]), dis[c[i]] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        vis[cur] = true;
        for (auto& to : g[cur]) {
            if (vis[to]) continue;
            dis[to] = min(dis[to], dis[cur] + 1);
            q.push(to);
        }
    }
    for (int j = 1; j <= k; j++) 
        f[j][i] = min(f[j][i], dis[c[j]]), f[i][j] = min(f[i][j], dis[c[j]]);
}

int main() {
    boost;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    cin >> k;
    for (int i = 1; i <= k; i++) cin >> c[i];
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            f[i][j] = 0x3f3f3f3f;
    for (int i = 1; i <= k; i++) bfs(i);
    //dp
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= k; i++) dp[1 << (i - 1)][i] = 1; //boundary
    for (int st = 1; st < (1 << k) - 1; st++) {
        for (int i = 0; i < k; i++) { //current node
            if (!((1 << i) & st)) continue;
            for (int j = 0; j < k; j++) {
                if ((1 << j) & st) continue;
                dp[st | (1 << j)][j + 1] = min(dp[st | (1 << j)][j + 1], dp[st][i + 1] + f[i + 1][j + 1]);
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= k; i++) ans = min(ans, dp[(1 << k) - 1][i]);
    if (ans == 0x3f3f3f3f) ans = -1;
    cout << ans << endl;
    return 0;
}