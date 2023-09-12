//luo gu P1004 1006
#include<bits/stdc++.h>
using namespace std;
int dp[10][10][10][10],n,x,y,z;
int val[10][10];
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin>>n;
    while(true){
        cin>>x>>y>>z;
        if(!x&&!y&&!z) break;
        val[x][y]=z;
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            for(int k=1; k<=n; k++)
                for(int l=1; l<=n; l++){
                    dp[i][j][k][l]=max(max(dp[i-1][j][k-1][l],dp[i-1][j][k][l-1]),max(dp[i][j-1][k-1][l],dp[i][j-1][k][l-1]))+val[i][j]+val[k][l];
                    if(i==k&&j==l) dp[i][j][k][l]-=val[k][l];
                    //(i,j)goes first, then(k,l) 
                    //if they are in the same way, we just add one val
                } 
    cout<<dp[n][n][n][n];
    return 0;
}