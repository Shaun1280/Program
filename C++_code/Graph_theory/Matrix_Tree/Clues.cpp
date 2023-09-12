#include <bits/stdc++.h>
#define int long long
//https://codeforces.ml/contest/156/problem/D 图联通生成树计数
using namespace std;

constexpr int MAXN = 1e5 + 5;

int n, m, k, cnt, ans(1);
array<int, MAXN> fa, vis, num;

inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) fa[r1] = r2;
}

signed main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, Union(u, v);
    for (int i = 1; i <= n; i++) {
        if (!vis[find(i)]) cnt++, vis[find(i)] = 1;
        num[find(i)]++;
    }
    for (int i = 1; i <= n; i++)
        if (num[i]) ans = ans * num[i] % k;
    for (int i = 1; i <= cnt - 2; i++)
        ans = ans * n % k;
    if (cnt == 1) ans = 1;
    cout << ans % k << endl;
    return 0;
}