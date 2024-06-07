#include<bits/stdc++.h>
const int MAXN=1e4+1;
using namespace std;
int n,Mine[MAXN],dp[MAXN][2][2];
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    /*
     *dp[i][j][k]
     * pos i
     * j=0, no mine exists at pos i 
     * j=1, mine exists at pos i
     * k=0, mine isn't needed in the next pos
     * k=1, mine needed in the next pos
     */
    cin>>n;
    dp[0][0][0]=dp[0][0][1]=1;
    for(int i=1; i<=n; i++) cin>>Mine[i];
    for(int i=1; i<=n; i++){
        switch (Mine[i])
        {
        case 0:
            dp[i][0][0]+=dp[i-1][0][0];
            continue;
        case 1:
            dp[i][0][0]+=dp[i-1][1][0];
            dp[i][1][0]+=dp[i-1][0][1];
            dp[i][0][1]+=dp[i-1][0][0];
            continue;
        case 2:
            dp[i][1][0]+=dp[i-1][1][1];
            dp[i][0][1]+=dp[i-1][1][0];
            dp[i][1][1]+=dp[i-1][0][1];
            continue;
        case 3:
            dp[i][1][1]+=dp[i-1][1][1];
            continue;
        }
    }
    printf("%d", dp[n][0][0]+dp[n][1][0]);
    return 0;
}