#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/1061/D
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e3 + 3, MOD = 1e9 + 7;

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
    string type;
    for (int t = 1; t <= m; t++) {
        int a, b, c;
        cin >> a >> b >> c >> type;
        a++, b++;
        if (type == "AND") {
            if (c == 0) add(a, b + n), add(b, a + n);
            else add(a + n, a), add(b + n, b);
        } else if (type == "OR") {
            if (c == 0) add(a, a + n), add(b, b + n);
            else add(a + n, b), add(b + n, a);
        } else {
            if (c == 0) add(a, b), add(b, a), add(a + n, b + n), add(b + n, a + n);
            else add(a, b + n), add(b, a + n), add(b + n, a), add(a + n, b);
        }
        /* Notice
         * (a & b) = 1 <=> (a | a) & (b | b)
         * (a or b) = 0 <=> (!a | !a) & (!b | !b)
         * (a xor b) = 0 <=> (!a | b) & (!b | a)
         * (a xor b) = 1 <=> (!a | !b) & (b | a)
         */
    }
    for (int i = 1; i <= 2 * n; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (belong[i] == belong[i + n]) {
            cout << "NO" << "\n";
            return 0;
        }
    cout << "YES" << "\n";
    return 0;
}