#include<bits/stdc++.h>
/*P4953 [USACO02FEB] Cow Cycling*/
using namespace std;
int N, E, D, Time = 0x7fffffff;
int dp[21][101][101]; /*还有i头牛 领头体力为j 其余牛体力为k 最终(假设有一头牛从来没有当过领头的)其余牛的体力都为跟随圈数E-D*/ 
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> N >> E >> D;
    if(E < D) printf("0");
    else{
        memset(dp, 0x3f, sizeof(dp));
        dp[N][E][E] = 0;
        for (int i = N; i>=1; i--) //还有j头牛
            for (int j = E; j >= 0; j--) //领头牛体力
                for (int k = E; k >=0; k--) //其余牛体力
                    for (int v = 1; v <=10; v++){ //速度
                        if(j - v * v >=0 && k - v >= 0) 
                            dp[i][j - v * v][k - v] = min(dp[i][j - v * v][k - v], dp[i][j][k] + 1);
                        if(k - v * v>= 0) /*还剩i-1头牛*/
                            dp[i - 1][k - v * v][k - v] = min(dp[i - 1][k - v * v][k - v], dp[i][j][k] + 1);
                    }
        for(int i = 1; i <= N; i++)
            for(int j = 0; j <= E; j++)
                Time = min(Time, dp[i][j][E - D]);
        cout<< Time;
    }
    return 0;
}