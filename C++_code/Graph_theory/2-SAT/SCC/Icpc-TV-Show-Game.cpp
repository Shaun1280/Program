#include <bits/stdc++.h>
// http://codeforces.com/gym/101987 K
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e4 + 4, MOD = 1e9 + 7;

int n, m, tot, top, cntscc;
vector<int> g[MAXN * 2];
int dfn[MAXN * 2], low[MAXN * 2], stk[MAXN * 2], ins[MAXN * 2], belong[MAXN * 2];
char ans[MAXN];
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
    string c[3];
    int l[3], p[3];
    for (int t = 1; t <= m; t++) { // 一个人猜 3 盏灯 a b c颜色 0/1，猜对至少 2 个则可满足
        for (int i = 0; i < 3; i++)
            cin >> l[i] >> c[i], p[i] = c[i] == "R" ? 1 : 0;
        // !a => (b & c)
        // !b => (a & c)
        // !c => (a & b)
        add(l[0] + (1 - !p[0]) * n, l[1] + (1 - p[1]) * n);
        add(l[1] + (1 - !p[1]) * n, l[0] + (1 - p[0]) * n);
        add(l[0] + (1 - !p[0]) * n, l[2] + (1 - p[2]) * n);
        add(l[2] + (1 - !p[2]) * n, l[0] + (1 - p[0]) * n);

        add(l[1] + (1 - !p[1]) * n, l[0] + (1 - p[0]) * n);
        add(l[0] + (1 - !p[0]) * n, l[1] + (1 - p[1]) * n);
        add(l[1] + (1 - !p[1]) * n, l[2] + (1 - p[2]) * n);
        add(l[2] + (1 - !p[2]) * n, l[1] + (1 - p[1]) * n);

        add(l[2] + (1 - !p[2]) * n, l[0] + (1 - p[0]) * n);
        add(l[0] + (1 - !p[0]) * n, l[2] + (1 - p[2]) * n);
        add(l[2] + (1 - !p[2]) * n, l[1] + (1 - p[1]) * n);
        add(l[1] + (1 - !p[1]) * n, l[2] + (1 - p[2]) * n);
    }
    for (int i = 1; i <= 2 * n; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (belong[i] == belong[i + n]) {
            cout << -1 << "\n";
            return 0;
        }
    for (int i = 1; i <= n; i++)
        ans[i] = belong[i] < belong[i + n] ? 'R' : 'B', cout << ans[i];
    return 0;
}