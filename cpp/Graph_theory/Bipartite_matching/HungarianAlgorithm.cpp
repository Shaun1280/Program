#include<bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e3 + 3;

int n, m, e, match[MAXN];
bool E[MAXN][MAXN], used[MAXN];

inline bool dfs(int x){
    for(int i = 1; i <= m; i++){
        if(E[x][i] && !used[i]){
            used[i] = true;
            if(!match[i] || dfs(match[i])){
                /*
                *如果这个点i还未匹配则pos和他匹配，如果这个点已经匹配，
                *那么如果本来和他匹配的点match[i]还能找到另一个点匹配则pos把i“抢”过来，
                *让match[i]去匹配另一个点，否则就不干涉i和match[i]匹配
                */
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> m >> e;
    for(int i = 1; i <= e; i++){
        int u, v;
        cin >> u >> v;
        if(u > n || v > m) continue;
        E[u][v] = 1;
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        memset(used, 0, sizeof(used));
        if(dfs(i)) cnt++;
    }
    cout << cnt << endl;
    return 0;
}