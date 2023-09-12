#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2704
using namespace std;

int n, m, dp[3][1 << 10][1 << 10], ans;
int mp[101];

struct node {
    int st, cnt;  // state and the number of soldiers
};
vector<vector<node> > state;

inline void Init() {
    for (int i = 1; i <= n; i++) {  //预处理每一层合法状态
        for (int st = 0; st < (1 << m); st++) {
            if ((st & (st << 1)) || (st & (st << 2)))
                continue;  //产生误伤的状态
            if ((st & (st >> 1)) || (st & (st >> 2)))
                continue;                         //产生误伤的状态
            if ((st | mp[i]) != mp[i]) continue;  //地形不符合要求
            int cnt = 0;
            for (int k = 0; k < m; k++)
                if (st & (1 << k)) cnt++;  //统计炮兵个数 也可lowbit
            state[i].push_back(node{st, cnt});
        }
    }
    for (auto i : state[1]) dp[1][i.st][0] = i.cnt;
    //第一层
    for (auto i : state[2])  //第二层
        for (auto j : state[1])
            if ((i.st & j.st) == 0) dp[2][i.st][j.st] = i.cnt + j.cnt;
    for (int i = 3; i <= n; i++)
        for (auto s1 : state[i]) {          //枚举当前行状态
            for (auto s2 : state[i - 1]) {  //枚举上一行状态
                if (s1.st & s2.st) continue;
                for (auto s3 : state[i - 2]) {  //枚举上上一行状态
                    if ((s1.st & s3.st) || (s2.st & s3.st)) continue;
                    dp[i % 3][s1.st][s2.st] =
                        max(dp[i % 3][s1.st][s2.st],
                            dp[(i - 1) % 3][s2.st][s3.st] + s1.cnt);
                    if (i == n) ans = max(ans, dp[i % 3][s1.st][s2.st]);
                }
            }
        }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    state.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            char c;
            cin >> c;
            if (c == 'P') mp[i] += 1 << j;
        }
    }
    Init();
    cout << ans << endl;
    return 0;
}