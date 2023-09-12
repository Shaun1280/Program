#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3959 P3959 宝藏
using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 13, MOD = 1e9 + 7;

int n, m, G[MAXN][MAXN], dp[MAXN][1 << MAXN], expand[1 << MAXN];
int cost[1 << MAXN][MAXN];
vector<pair<int, int>> valid[1 << MAXN];

void init() {
    for (int k = 0; k < (1 << n); k++) {
        expand[k] = k; //状态 k 扩展一层的状态
        for (int i = 0; i < n; i++) {
            if (k & (1 << i)) { //状态 k 中已打通的点
                for (int to = 0; to < n; to++) {
                    if (G[i][to] != 0x3f3f3f3f && (k & (1 << to)) == 0) {
                        expand[k] |= (1 << to); //k所能到达的下一层状态
                        cost[k][to] = min(cost[k][to], G[i][to]);
                        //状态 k 扩展到 to 的最短边
                    }
                }
            }
        }
        for (int j = 0; j < (1 << n); j++) {
            if (k == j) continue;
            if ((k & j) == k && (expand[k] & j) == j) {
                int tmp = k ^ j, sum = 0;
                for (int i = 0; i < n; i++) {
                    if (tmp & (1 << i)) sum += cost[k][i];
                }
                valid[k].emplace_back(j, sum);
            }
        }
    }
}

void DP(int ans = 0x3f3f3f3f) { //dp[i][st] 打通 i 层, 状态为 st
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) dp[1][1 << i] = 0;
    for (int i = 2; i <= n; i++)
        for (int k = 0; k < (1 << n); k++) {
            for (auto& e : valid[k]) {
                int st = e.first, sum = e.second;
                dp[i][st] = min(dp[i][st], dp[i - 1][k] + (i - 1) * sum);
            }
        }
    for (int i = 1; i <= n; i++) ans = min(ans, dp[i][(1 << n) - 1]);
    printf("%d\n", ans);
}

int main() {
    read(n, m);
    memset(G, 0x3f, sizeof(G)), memset(cost, 0x3f, sizeof(cost));
    for (int i = 1, u, v, w; i <= m; i++) {
        read(u, v , w), u--, v--;
        G[u][v] = min(G[u][v], w);
        G[v][u] = min(G[v][u], w);
    }
    init();
    DP();
    return 0;
}