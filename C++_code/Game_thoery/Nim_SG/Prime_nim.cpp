#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1857 质数取石子
using namespace std;

constexpr int MAXN = 2e4 + 4;

int tc, n, ans = 1e9, sg[MAXN], dp[MAXN];
vector<int> prime;
bool isprime[MAXN];

inline void eluer_seive() {
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    for (int i = 2; i < MAXN; i++) {
        if (isprime[i]) prime.push_back(i);
        for (auto& j : prime) {
            if (i * j > MAXN) break;
            isprime[i * j] = false;
            if (i % j == 0) break;
        }
    }
}

inline int SG(int cur) {
    if (sg[cur] != -1) return sg[cur];
    vector<bool> vis(prime.size() + 1);
    fill(vis.begin(), vis.end(), false);
    for (auto& i : prime) {
        if (i > cur) break;
        vis[SG(cur - i)] = true;
    }
    int mex = 0;
    while (vis[mex]) mex++;
    return sg[cur] = mex;
}

inline int DP(int cur) { //dp n n个石头子的步数
    if (dp[cur] != -1) return dp[cur];
    int mi = 1e9, mx = 0;
    for (auto& i : prime) {
        if (i > cur) break;
        DP(cur - i);
        if (sg[cur] && !sg[cur - i]) mi = min(mi, DP(cur - i) + 1);
        else if (!sg[cur] && sg[cur - i]) mx = max(mx, DP(cur - i) + 1);
    }
    return dp[cur] = (sg[cur]? mi : mx);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    eluer_seive();
    memset(sg, -1, sizeof(sg)), memset(dp, -1, sizeof(dp));
    sg[0] = sg[1] = dp[0] = dp[1] = 0;
    SG(MAXN - 1), DP(MAXN - 1);
    cin >> tc;
    while (tc--) {
        cin >> n;
        cout << (sg[n] ? dp[n] : -1) << "\n";
    }
    return 0;
}