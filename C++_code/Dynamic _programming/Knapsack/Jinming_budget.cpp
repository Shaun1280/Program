#include <bits/stdc++.h>
const int MAXN = 61;
const int MAXM = 3e4 + 1;
using namespace std;  // appedix staple
struct node {
    int v, p, q;
} goods[MAXN], staple[MAXN][MAXN];  // i 的第j个附件的 v p
int Cnt_append[MAXN];               // i的附件个数
int n, m, tot;
int dp[MAXM], cnt[MAXN];
int V[MAXN][MAXN], P[MAXN][MAXN];
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    int v, p, q;
    for (int i = 1; i <= m; i++) {
        cin >> v >> p >> q;
        goods[i].v = v, goods[i].p = p * v, goods[i].q = q;
        if (q)
            Cnt_append[q]++, staple[q][Cnt_append[q]].v = v,
                             staple[q][Cnt_append[q]].p = v * p;
    }
    for (int i = 1; i <= m; i++) {
        if (Cnt_append[i]) {  //只买附件
            memset(dp, -1, sizeof(dp));
            dp[0] = 0;
            for (int j = 1; j <= Cnt_append[i]; j++) {
                for (int k = n - goods[i].v; k >= staple[i][j].v; k--)
                    if ((dp[k] < dp[k - staple[i][j].v] + staple[i][j].p) &&
                        dp[k - staple[i][j].v] != -1)
                        dp[k] = dp[k - staple[i][j].v] + staple[i][j].p,
                        cout << dp[k] << endl;
            } /*0 1 背包
             suppose staple is i;
             dp[k] means when cost is k, the max v*k that can be created*/
            for (int j = 0; j <= n - goods[i].v; j++) {
                if (dp[j] == -1) continue;  // not a legal cost
                cnt[i]++;
                V[i][cnt[i]] = j + goods[i].v;
                P[i][cnt[i]] = dp[j] + goods[i].p;  //所有附件还需要一个主件
            }  //分组背包预处理 第i个主件 有cnt[i]个附件时的v 最大v*p +
               //goods[i].v
        } else if (!goods[i].q) {  //只买主件的情况
            cnt[i]++;
            V[i][cnt[i]] = goods[i].v;
            P[i][cnt[i]] = goods[i].p;
        }
    }
    /*分组背包*/
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
        for (int j = n; j >= 0;
             j--)  //对于每个主键 求出当前体积j 对应的v*p的最大值
            for (int k = 1; k <= cnt[i]; k++)
                if (j >= V[i][k]) dp[j] = max(dp[j], dp[j - V[i][k]] + P[i][k]);
    for (int i = 0; i <= n; i++) tot = max(tot, dp[i]);
    cout << tot;
    return 0;
}