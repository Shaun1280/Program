#include <bits/stdc++.h>
//P4111 [HEOI2015]小 Z 的房间 https://www.luogu.com.cn/problem/P4111
using namespace std;
using LL = long long;

constexpr int MAXN = 2000;
constexpr int MOD = 1e9;

int n, m, tot, mp[MAXN][MAXN];

LL G[MAXN][MAXN];
inline LL Gauss() {
    LL ans = 1;
    for (int i = 1; i < tot; i++) {
        for (int j = i + 1; j < tot; j++)
            while (G[j][i]) {
                LL t = G[i][i] / G[j][i];
                for (int k = i; k < tot; k++)
                    G[i][k] = ((G[i][k] - t * G[j][k]) % MOD + MOD) % MOD;
                swap(G[i], G[j]);
                ans = -ans;
            }
        ans = ans * G[i][i] % MOD;
    }
    return (ans + MOD) % MOD;
}

inline void add(int u, int v) {
    if (u > v) return;
    G[u][u]++, G[v][v]++;
    G[u][v]--, G[v][u]--;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            if (ch == '.') mp[i][j] = ++tot;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int u = mp[i][j], v;
            if (!u) continue;
            if (v = mp[i - 1][j]) add(u, v);
            if (v = mp[i + 1][j]) add(u, v);
            if (v = mp[i][j - 1]) add(u, v);
            if (v = mp[i][j + 1]) add(u, v);
        }
    cout << Gauss() << endl;
    return 0;
}