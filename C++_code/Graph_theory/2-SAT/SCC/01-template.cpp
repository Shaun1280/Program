#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P4782
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7;

int n, m, tot, top, cntscc;
vector<int> g[MAXN * 2];
int dfn[MAXN * 2], low[MAXN * 2], stk[MAXN * 2], ins[MAXN * 2], belong[MAXN * 2], ans[MAXN];
// vector<int> scc[MAXN]

void add(int u, int v) { g[u].emplace_back(v); }

void tarjan(int cur) {
    dfn[cur] = low[cur] = ++tot;
    stk[++top] = cur, ins[cur] = true;
    for (const auto& to : g[cur]) {
        if (!dfn[to]) {
            tarjan(to);
            low[cur] = min(low[cur], low[to]);
        } else if (ins[to]) {
            low[cur] = min(low[cur], dfn[to]);
        }
    }
    if (dfn[cur] == low[cur]) {
        ++cntscc;
        int tmp;
        do {
            tmp = stk[top--];
            ins[tmp] = false;
            belong[tmp] = cntscc;
        } while (cur != tmp);
    }
}


int main() {
    boost;
    cin >> n >> m;
    for (int t = 1; t <= m; t++) {
        int i, a, j, b;
        cin >> i >> a >> j >> b; // xi = a or xj = b & a,b = 0 or 1
        add(i + (1 - (!a)) * n, j + (1 - b) * n);
        add(j + (1 - (!b)) * n, i + (1 - a) * n);
    }
    for (int i = 1; i <= 2 * n; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (belong[i] == belong[i + n]) {
            cout << "IMPOSSIBLE" << "\n";
            return 0;
        }
    cout << "POSSIBLE" << "\n";
    for (int i = 1; i <= n; i++) // !x -> x thus x = ture in rev topo order
        ans[i] = belong[i] < belong[i + n], cout << ans[i] << " ";
    return 0;
}