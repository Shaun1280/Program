#include <bits/stdc++.h>
// P1896 [SCOI2005]互不侵犯
// https://www.luogu.com.cn/problem/P1896
typedef long long LL;
using namespace std;
int n, k, ans;
LL dp[10][1 << 10][100];  // i行, 状态为j, k个国王
struct node {
    int st, cnt_king;
};
vector<node> State;
inline void Init() {
    for (int st = 0; st < (1 << n); st++) {
        if (st & (st << 1)) continue;  //两个国王相邻
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (st & (1 << i))  //该状态能放置的国王数
                cnt++;
        State.push_back(node{st, cnt});
    }
}
int main() {
    cin >> n >> k;
    Init();  //预处理行状态
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)                //枚举行数
        for (int j = 0; j < State.size(); j++)  //枚举当前行状态
            for (int king = 0; king <= k;
                 king++) {  // i行Statej状态下当前国王总数
                if (king < State[j].cnt_king)
                    continue;  //总国王个数小于当前行国王个数 跳过
                for (int t = 0; t < State.size(); t++) {  //枚举上一行状态
                    if (State[t].st & State[j].st) continue;
                    if (State[t].st & (State[j].st >> 1)) continue;
                    if (State[t].st & (State[j].st << 1)) continue;
                    dp[i][State[j].st][king] +=
                        dp[i - 1][State[t].st][king - State[j].cnt_king];
                }
            }
    LL ans = 0;
    for (auto i : State) ans += dp[n][i.st][k];
    cout << ans;
    return 0;
}