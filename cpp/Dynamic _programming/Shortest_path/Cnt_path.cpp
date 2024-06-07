#include<bits/stdc++.h>
const int MAXN = 2e3 + 1;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f; 
}
struct E{
    int to, next, w;
    E(){}
    E(int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXN * MAXN];
int connected[MAXN][MAXN];
struct node{
    int p, dis;
    inline friend bool operator < (const node &a, const node &b){
        return a.dis > b.dis;
    }
};
int dis[MAXN], dp[MAXN], vis[MAXN], head[MAXN], tot;
inline void add_egde(int from, int to, int w){
    Edge[tot] = (E){to, w, head[from]};
    head[from] = tot++;
}
priority_queue<node, vector<node>>q;
int n, m;
inline void dijkstra(){
    memset(dis, 0x3f, sizeof(dis));
    dp[1] = 1;
    q.push((node){1, dis[1] = 0});
    while(!q.empty()){
        int cur = q.top().p;
        q.pop();
        if(vis[cur]) continue;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to, w = Edge[i].w;
            if(dis[to] > dis[cur] + w){
                dis[to] = dis[cur] + Edge[i].w;
                q.push((node){to, dis[to]});
                dp[to] = dp[cur];
            } else if(dis[to] == dis[cur] + w) 
                dp[to] = dp[cur] + dp[to];
        }
        vis[cur] = true;
    }
    if(dis[n] == 0x3f3f3f3f) cout << "No answer";
    else cout << dis[n] << " " << dp[n];
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    int u, v, w;
    while(m--){
        u = read(), v = read(), w = read();
        if(!connected[u][v] || connected[u][v] > w)
            connected[u][v] = w;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(connected[i][j]) add_egde(i, j, connected[i][j]);
    dijkstra();
    return 0;
}