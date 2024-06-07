#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc219/tasks/abc219_g
// G-propagation
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n, m, q, B;
int tag[MAXN], changed[MAXN], resq[MAXN], col[MAXN];
vector<int> g[MAXN], f[MAXN];

void getCurValue(int x) {
    int tmp(0);
    for (auto& to : f[x]) tmp = max(tmp, tag[to]);
    if (tmp && tmp > changed[x]) col[x] = resq[tmp];
}

int main() {
    boost;
    cin >> n >> m >> q;
    B = sqrt(3 * m / 2 );
    for (int i = 1; i <= n; i++) col[i] = i;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        for (auto& to : g[i])
            if (g[to].size() >= B) f[i].push_back(to);

    for (int i = 1, x; i <= q; i++) {
        cin >> x;
        getCurValue(x); // get correct value
        resq[i] = col[x];

        if (g[x].size() < B) { // propagation
            for (auto& to : g[x]) col[to] = resq[i], changed[to] = i;
        } else { tag[x] = i; }
    }
    for (int i = 1; i <= n; i++) {
        getCurValue(i);
        cout << col[i] << " ";
    }
    return 0;
}