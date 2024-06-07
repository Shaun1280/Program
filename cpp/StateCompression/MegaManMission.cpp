#include <bits/stdc++.h>
constexpr int Inf = 0x3f3f3f3f;
// https://www.luogu.com.cn/blog/user48611/uva11795-mega-mans-mission
const int MAXN = 17;
using namespace std;
int testCase, N;
int weapon[MAXN] /*第i个机器人掉落的武器*/;
int state[1 << MAXN];  //机器人被击杀状态下拥有的武器
long long dp[1 << MAXN];
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> testCase;
    for (int t = 1; t <= testCase; t++) {
        scanf("%d", &N);
        memset(weapon, 0, sizeof(weapon));
        memset(state, 0, sizeof(state));
        memset(dp, 0, sizeof(dp));
        getchar();
        for (int i = 0; i < N; i++) {
            char c = getchar();
            if (c == '1') weapon[0] |= (1 << i);
        }
        for (int i = 1; i <= N; i++) {
            getchar();
            for (int j = 0; j < N; j++) {
                char c = getchar();
                if (c == '1') weapon[i] |= (1 << j);
            }
        }
        for (int st = 0; st < (1 << N); st++) {  //机器人被击杀的状态
            state[st] |= weapon[0];
            for (int j = 0; j < N; j++)
                if (st & (1 << j)) state[st] |= weapon[j + 1];
        }
        dp[0] = 1;
        for (int st = 1; st < (1 << N); st++) {
            for (int j = 0; j < N; j++) {
                if ((st & (1 << j)) && ((state[st ^ (1 << j)]) & (1 << j)))
                    dp[st] += dp[st ^ (1 << j)];
            }
        }
        printf("Case %d: %lld\n", t, dp[(1 << N) - 1]);
    }
    return 0;
}