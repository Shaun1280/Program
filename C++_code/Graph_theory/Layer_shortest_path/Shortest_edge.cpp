#include<bits/stdc++.h>
//P1948 [USACO08JAN]电话线Telephone Lines
const int MAXN = 1e6 + 6;
const int Inf = 0x3f3f3f3f;
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
}Edge[MAXN];
struct node{
    int p,  dis;
    inline friend bool operator < (const node &a, const node &b){
        return a.dis > b.dis;
    }
};
int vis[MAXN], head[MAXN], tot;
int dis[MAXN], minTime = Inf;
inline void add_edge(int from, int to, int w){
    Edge[tot] = (E){to, w, head[from]};
    head[from] = tot++;
}
priority_queue<node, vector<node>>q;
int n, m, k;
inline void dijkstra(){
    for(int i = 0 ; i <= n * k + n; i++) dis[i] = Inf;
    q.push((node){1, dis[1] = 0LL});
    while(!q.empty()){
        int cur = q.top().p;
        q.pop();
        if(vis[cur]) continue;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to, w = Edge[i].w;
            if(dis[to] > max(dis[cur], Edge[i].w)){
                dis[to] = max(dis[cur], Edge[i].w);
                q.push((node){to, dis[to]});
            }  
        }
        vis[cur] = true;
    }
    minTime = min(minTime, dis[n + k * n]);
    cout << (minTime == Inf ? -1 : minTime)<< endl;
}
int main(){
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    while(m--){
        int u, v, w;
        u = read(), v = read(), w = read();
        for(int i = 0; i <= k; i++)
            add_edge(u + i * n, v + i * n, w), add_edge(v + i * n, u + i * n, w);
        for(int i = 0; i < k; i++)
            add_edge(u + i * n, v + (i + 1) * n, 0), add_edge(v + i * n, u + (i + 1) * n, 0);
    }
    dijkstra();
    return 0;
}