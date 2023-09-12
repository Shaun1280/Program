#include <bits/stdc++.h>
// 长链剖分 https://oi-wiki.org/graph/hld/
// Dominant Indices https://codeforces.com/contest/1009/problem/F
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7;

vector<int> g[MAXN];
array<int, MAXN> fa, hSon, hg, in;
int* dp[MAXN], tmp[MAXN], ans[MAXN];

void dfs1(int cur, int f) {
    hg[cur] = 1, fa[cur] = f; // hg 到叶节点的距离
    for (auto& to : g[cur]) {
        if (to == f) continue;
        dfs1(to, cur);
        hg[cur] = max(hg[cur], hg[to] + 1);
        if (!hSon[cur] || hg[to] > hg[hSon[cur]]) hSon[cur] = to;
    }
}

void dfs2(int cur, int f) {
    static int tim;
    in[cur] = ++tim; // dfn
    dp[cur] = tmp + in[cur]; // 获取 dp[cur] 起始位置
    if (!hSon[cur]) return;
    dfs2(hSon[cur], f); // 优先重链
    for (auto& to : g[cur]) { // 轻儿子
        if (to != hSon[cur] && to != fa[cur]) dfs2(to, to);
    }
}

void DP(int cur) { // dpi,j 表示 i 的子树内，和 i 距离为 j 的点数
    if (hSon[cur]) DP(hSon[cur]), ans[cur] = ans[hSon[cur]] + 1;
    dp[cur][0] = 1;
    if (dp[cur][0] >= dp[cur][ans[cur]]) ans[cur] = 0;
    for (auto& to : g[cur]) {
        if (to != fa[cur] && to != hSon[cur]) { // light son
            DP(to);
            int len = hg[to];
            for (int i = 0; i < len; i++) {
                dp[cur][i + 1] += dp[to][i];
                if (dp[cur][i + 1] > dp[cur][ans[cur]]) ans[cur] = i + 1;
                if (dp[cur][i + 1] == dp[cur][ans[cur]] && i + 1 < ans[cur]) ans[cur] = i + 1;
            }
        }
    }
}

int main() {
    boost;
    int n;
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    DP(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
    return 0;
}