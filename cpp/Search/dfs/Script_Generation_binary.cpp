#include<bits/stdc++.h>
using namespace std;
//CF177F2 Script Generation
int n, k, t, cnt;
int r[21][21], matched[21];
void dfs(int mid, int heroId, int sum){
    if(heroId > n){
        cnt++;
        return;
    }
    if(cnt >= t) return;
    dfs(mid, heroId + 1, sum);
    for(int i = 1; i <= n; i++){
        if(matched[i] || !r[heroId][i] || sum + r[heroId][i] > mid) continue;
        matched[i] = true;
        dfs(mid, heroId + 1, sum + r[heroId][i]);
        matched[i] = false;
    }
}
inline void Binary_search(int l, int r){
    while(l <= r){
        int mid = l + r >> 1;
        cnt = 0, memset(matched, 0, sizeof(matched));
        dfs(mid, 1, 0);
        if(cnt >= t) r = mid - 1;
        else l = mid + 1;
    }
    cout << l << endl;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> k >> t;
    int u, v, w;
    for(int i = 1; i <= k; i++){
        cin >> u >> v >> w;
        r[u][v] = w;
    }
    Binary_search(0, 1e5);
    return 0;
}