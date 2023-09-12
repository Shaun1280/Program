#include <bits/stdc++.h>
//[SHOI2016]黑暗前的幻想乡 https://www.luogu.com.cn/problem/P4336
using namespace std;
using LL = long long;

constexpr int MOD = 1e9 + 7;

int n, m, tot;
vector<pair<int, int>> vec[20];

LL G[20][20];
inline LL Gauss() {
    LL ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            while (G[j][i]) {
                LL t = G[i][i] / G[j][i];
                for (int k = i; k < n; k++)
                    G[i][k] = ((G[i][k] - t * G[j][k]) % MOD + MOD) % MOD;
                swap(G[i], G[j]);
                ans = -ans;
            }
        ans = ans * G[i][i] % MOD;
    }
    return (ans + MOD) % MOD;
}

inline void add(int u, int v) {
    G[u][u]++, G[v][v]++;
    G[u][v]--, G[v][u]--;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0, cnt; i < n - 1; i++) {
        cin >> cnt;
        for (int j = 1, u, v; j <= cnt; j++) {
            cin >> u >> v;
            vec[i].emplace_back(u, v);
        }
    }
    LL ans = 0;
    for (int st = 0; st < (1 << (n - 1)); st++) {
        int cnt = 0;
        memset(G, 0, sizeof(G));
        for (int i = 0; i < n - 1; i++)
            if (st & (1 << i)) {
                for (auto& e : vec[i])
                    add(e.first, e.second);
                cnt++;
            }
        if ((n - cnt - 1) & 1) ans = (ans - Gauss()) % MOD;
        else ans = (ans + Gauss()) % MOD; //容斥原理
    }
    cout << (ans + MOD) % MOD << endl;
    return 0;
}