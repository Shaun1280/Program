#include <bits/stdc++.h>
//https://codeforces.ml/contest/1241/problem/E
using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 5e5 + 5, MOD = 1e9 + 7;

int q;
long long dp[MAXN][2];
//dp[i][0] 与父亲f没有相同颜色 即不选edge(f, i)子树的最大值 //dp[i][1] 与f有相同颜色的最大值
int n, k;
vector<pair<int, int>> g[MAXN];

void DP(int cur, int f) {
    vector<long long> vec;
    for (auto& e : g[cur]) {
        int to = e.first, w = e.second;
        if (to == f) continue;
        DP(to, cur);
        dp[cur][0] += dp[to][0];
        dp[cur][1] += dp[to][0]; //先不选这条边
        vec.push_back(dp[to][1] + w - dp[to][0]); //选这条边的贡献差值
    }
    sort(vec.begin(), vec.end(), [](const int& a, const int& b) { return a > b; });
    for (int i = 0; i < vec.size() && i < k; i++) { //前 k 大
        if (vec[i] < 0) break;
        if (i < k - 1) dp[cur][1] += vec[i]; //与cur父亲有相同颜色，只选 k - 1 条边
        dp[cur][0] += vec[i]; //cur与父亲没有相同颜色，选 k 条与子树相连的边
    }
}

int main() {
    read(q);
    while (q--) {
        read(n, k);
        for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = 0, g[i].clear();
        for (int i = 1, u, v, w; i < n; i++) {
            read(u, v, w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        DP(1, 0);
        printf("%lld\n", max(dp[1][0], dp[1][1]));
    }
    return 0;
}