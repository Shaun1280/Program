#include <bits/stdc++.h>
// 在树上选至少两个点，使得这些点两两之间距离都为直径，求方案数 % 998244353
// 先二次 dfs 求出直径
// 若直径为奇数，选取直径上距离终点为 d / 2, d / 2 + 1 的点，分为两个子树
// 设子树中距离子树根的距离为 d / 2 的点数为 m1, m2，则答案为 m1, m2
// 若直径为偶数，找到直径终点 C
// 求出与 C 相连的节点 A1, ..., Am
// 求出子树中与 C 距离为 d / 2 的节点数 mi
// 答案为 (m1 + 1)*...*(mm + 1) - (m1 + ... + mm) - 1
// 即所有选择方案减去 (全部都不选择) + (只选择一个点的方案数)
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 998244353;

int n, diaDis[MAXN], pre[MAXN], dia, ed, mid;

vector<int> g[MAXN];

void diadfs(int cur, int fa) {
    for (auto& to : g[cur]) {
        if (to == fa) continue;
        diaDis[to] = diaDis[cur] + 1, pre[to] = cur;
        if (diaDis[to] > dia) dia = diaDis[to], ed = to;
        diadfs(to, cur);
    }
}

void getDia() {
    dia = INT_MIN, diadfs(1, 0);
    diaDis[ed] = 0, pre[ed] = 0, dia = INT_MIN;
    diadfs(ed, 0);
}

int getVertex(int ed, int k) { // 到终点距离为 k
    while (k--) ed = pre[ed];
    return ed;
}

int dfs(int cur, int f, int d) {
    if (!d) return 1;
    int res = 0;
    for (auto& to: g[cur]) {
        if (to == f) continue;
        res += dfs(to, cur, d - 1);
    }
    return res;
}

signed main() {
    boost;
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    getDia();
    if (dia & 1) {
        int A = getVertex(ed, dia / 2 + 1), B = getVertex(ed, dia / 2);
        int m1 = dfs(A, B, dia / 2), m2 = dfs(B, A, dia / 2);
        cout << 1LL * m1 * m2 % MOD << "\n";
    } else {
        int C = getVertex(ed, dia / 2);
        vector<int> m;
        for (auto& to : g[C]) {
            int tmp = dfs(to, C, dia / 2 - 1);
            m.push_back(tmp);
        }
        int res = 1;
        for (auto& i : m) res = 1LL * res * (i + 1) % MOD;
        for (auto& i : m) res = (res - i) % MOD;
        res = (res - 1) % MOD;
        cout << (res + MOD) % MOD << "\n";
    }
    return 0;
}