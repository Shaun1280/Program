#include<bits/stdc++.h>
const int MAXN = 2e2 + 1;
#define Inf 0x3f3f3f3f
using namespace std;
int n, m, Q;
vector<int>T;
int f[MAXN][MAXN];
int Min[MAXN][MAXN][MAXN];
inline void Floyd(){
    for(int k = 0; k < n; k++) //枚举中转点k
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)   
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]), 
                Min[i][j][k] = min(Min[i][j][k], f[i][j]);
                //i, j在T[k]时刻的最短路径值
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n >> m, T.resize(n);
    memset(f, 0x3f, sizeof(f));
    memset(Min, 0x3f, sizeof(Min));
    for(int i = 0; i < n; i++) cin >> T[i];
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        f[u][v] = f[v][u] = w; //双向边
    }
    Floyd();
    cin >> Q;
    while(Q--){
        int x, y, t;
        cin >> x >> y >> t;
        int pos = upper_bound(T.begin(), T.end(), t) - T.begin();
        //求出T中第一个比t大的元素的index 要最短路径的就是Min[x][y][Index - 1]
        if(T[x] > t || T[y] > t || Min[x][y][pos - 1] == Inf) cout << -1 << endl;
        else cout << Min[x][y][pos - 1] << endl;
    }
    return 0;
}