#include<bits/stdc++.h>
const int MAXN = 20;
//https://www.luogu.com.cn/problem/P1171   CH 0103
using namespace std;
int n, E[MAXN][MAXN], dp[1 << MAXN][MAXN]; //点被经过对应二进制状态i, 处于j点
inline int read(){
    int x = 0;
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x;
}
int main(){
    n = read();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            E[i][j] = read();
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for(int i = 1; i < (1 << n); i++)
        for(int j = 0; j < n; j++)
            if((i >> j) & 1) //j为当前点被访问过
                for(int k = 0; k < n; k++)
                    if((i ^ (1 << j)) >> k & 1) //j未被访问时k已被访问
                        dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)/*j未访问,k已访问的状态*/][k] + E[k][j]);
    int ans = 0x3f3f3f3f;
    for(int i = 1; i < n; i++)
        ans = min(ans, dp[(1 << n) - 1][i] + E[i][0]);
    cout << ans;
    return 0;
}