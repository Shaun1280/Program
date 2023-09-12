#include<bits/stdc++.h>
const int MAXN = 5e3 + 5;
//https://www.luogu.com.cn/problem/P2280
//P2280 [HNOI2003]激光炸弹
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int n, R, G[MAXN][MAXN], ans;   
int main(){
    n = read(), R = read();
    for(int i = 1; i <= n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        G[u + 1][v + 1] = w;
    }
    for(int i = 1; i <= MAXN - 4; i++)
        for(int j = 1; j <= MAXN - 4; j++)
            G[i][j] = G[i][j] + G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1];
    for(int i = R; i <= MAXN - 4; i++)
        for(int j = R; j <= MAXN - 4; j++){
            ans = max(ans, G[i][j] - G[i - R][j] - G[i][j - R] + G[i - R][j - R]);
        }
    cout << ans;
    return 0;
}