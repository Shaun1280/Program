#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
int Class[301][301];
int n, m, ans;
int G[301][301];
int zeroDis[301][301];
int min(int a, int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            scanf("%d", &Class[i][j]);
            G[i][j] = G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1] + Class[i][j];
        }     
    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= n; i++)
            if(Class[i][j])
                zeroDis[i][j] = zeroDis[i - 1][j] + 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int minDis = 0x3f3f3f3f;
            for(int k = j; k <= m && Class[i][k]; k ++){
                minDis = min(minDis, zeroDis[i][k]);
                ans = max(ans, G[i][k] + G[i - minDis][j - 1] - G[i][j - 1] - G[i - minDis][k]);
            }
        }
    }   
    printf("%d\n", ans);
    return 0;
}