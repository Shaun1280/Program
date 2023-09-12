#include<bits/stdc++.h>
//P1717 钓鱼
const int MAXN = 26;
using namespace std;
int N, H;
int f[MAXN], d[MAXN]/*decrease*/, t[MAXN];
int dp[MAXN][200], Max;
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> N >> H, H = H * 12;
    for(int i = 1; i <= N; i++) cin >> f[i];
    for(int i = 1; i <= N; i++) cin >> d[i];
    for(int i = 2; i <= N; i++) 
        cin >> t[i];
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for(int T = 1; T <= H; T++)
        for(int i = 1; i <= N; i++)
            for(int k = 0; k <= T - t[i]; k++){
                if(f[i] > (k - 1) * d[i] && ~dp[i - 1][T - t[i] - k])
                dp[i][T] = max(dp[i][T], dp[i - 1][T - t[i] - k] + (2 * f[i] - (k - 1) * d[i]) * k / 2);
                Max= max(Max, dp[i][T]);
            }
    cout << Max;
    return 0;
}