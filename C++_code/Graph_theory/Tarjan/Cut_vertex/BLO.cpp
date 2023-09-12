#include <bits/stdc++.h>
#define int long long
//https://www.luogu.com.cn/problem/P3469 P3469 [POI2008]BLO-Blockade
using namespace std;
//节点i被删除后有对少个点对不再联通
constexpr int MAXN = 1e5 + 5;

struct Edge {
    Edge() = default;
    Edge(int _to, int _next) : to(_to), next(_next) {}
    int to, next;
};
vector<Edge> edge;
array<int, MAXN> sz, dfn, low, head, ans, cut;
int n, m;

inline void addEdge(int from, int to) {
    edge.emplace_back(to, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, head[to]), head[to] = edge.size() - 1;
}

void tarjan(int cur) {
    static int tot;
    dfn[cur] = low[cur] = ++tot, sz[cur] = 1;
    int cnt(0), sum(0);
    for (int i = head[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (!dfn[to]) {
            tarjan(to);
            low[cur] = min(low[cur], low[to]);
            sz[cur] += sz[to];
            if (dfn[cur] <= low[to]) {
                cnt++;
                ans[cur] += sz[to] * (n - sz[to]);
                sum += sz[to];
                if (cur != 1 || cnt >= 2) cut[cur] = true; //是割点
            }
        } else low[cur] = min(low[cur], dfn[to]);
    }
    if (cut[cur]) ans[cur] += (n - 1) + (n - 1 - sum) * (1 + sum);
    else ans[cur] = 2 * (n - 1); //不是割点 覆盖原答案
}

signed main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    fill(head.begin(), head.end(), -1);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        addEdge(u, v);
    }
    tarjan(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
}