#include<bits/stdc++.h>
#define Inf 0x3f3f3f3f
const int MAXN = 1e2 + 1;
using namespace std;
int G[MAXN][MAXN], inq[MAXN], pre[MAXN], dis[MAXN];
int Time, n, m;
inline int spfa(int s, int t){
    deque <int> q;
    memset(inq, 0, sizeof(inq));
    for(int i = 1; i <= n; i++) dis[i] = Inf;
    q.push_front(s), inq[s] = true, dis[s] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for(int to = 1; to <= n; to++){
            if(G[cur][to] == Inf) continue;
            if(dis[to] > dis[cur] + G[cur][to]){
                dis[to] = dis[cur] + G[cur][to];
                pre[to] = cur;
                if(!inq[to]){
                    if(q.empty() || dis[to] < dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
    return dis[t];
}
inline void change(int x){
    if(x == 1) return;
    G[pre[x]][x] = -G[pre[x]][x];
    G[x][pre[x]] = Inf;
    change(pre[x]);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    while(true){
        Time = Inf;
        cin >> n; 
        if(n == 0) break;
        cin >> m;
        int u, v, w;
        memset(G, 0x3f, sizeof(G));
        memset(pre, 0, sizeof(pre));
        for(int i = 1; i <= m; i++){
            cin >> u >> v >> w;
            G[u][v] = G[v][u] = w;
        }
        Time = spfa(1, n);
        change(n);
        Time = Time + spfa(n, 1);
        if(Time >= Inf) cout << "Back to jail" << endl;
        else cout << Time << endl;
    }
    return 0;
}