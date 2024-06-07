#include <bits/stdc++.h>
// P4322 [JSOI2016]最佳团体
const int MAXN = 3e3;
const int Inf = 0x3f3f3f3f;
const double EPSILON = 1e-4;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node {
    int to, next;
    node() {}
    node(int _to, int _next) { to = _to, next = _next; }
} Edge[MAXN];
int siz[MAXN], head[MAXN], tot;
int in[MAXN], nxt[MAXN], tim /*dfs_time*/;
inline void add_edge(int from, int to) {
    Edge[tot] = (node){to, head[from]};
    head[from] = tot++;
}
void dfs(int u) {
    in[u] = tim++;  // 0号节点dfs序为0
    for (int i = head[u]; ~i; i = Edge[i].next) dfs(Edge[i].to);
    nxt[in[u]] = tim;  // in所对应的out
}
int n, k;
int cost[MAXN], p[MAXN];
double dp[MAXN][MAXN], w[MAXN];
inline bool check(double x) {
    for (int i = 1; i <= n; i++)
        w[in[i]] = 1.0 * p[i] - x * cost[i];  //每个节点dfs序下的权值
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = .0;
    for (int i = 0; i <= n; i++)                  // dfs序 即in = i的节点
        for (int j = 0; j <= min(i, k + 1); j++)  //选择了j个人
            if (dp[i][j] > -Inf) {
                dp[i + 1][j + 1] = fmax(dp[i + 1][j + 1], dp[i][j] + w[i]);
                //选取节点i的w 并将结果保存到dfs序 = i + 1 的节点中
                dp[nxt[i]][j] = fmax(dp[nxt[i]][j], dp[i][j]);
                //不再继续向下选取 状态转移到另一个子树根节点
            }
    return dp[n + 1][k + 1] > 0;
}
inline void Binary_search(double l, double r) {
    while (l + EPSILON < r) {
        double mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.3f", l);
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    k = read(), n = read();
    for (int i = 1, R; i <= n; i++)
        cost[i] = read(), p[i] = read(), R = read(), add_edge(R, i);
    dfs(0);
    Binary_search(.0, 1e4);
    return 0;
}