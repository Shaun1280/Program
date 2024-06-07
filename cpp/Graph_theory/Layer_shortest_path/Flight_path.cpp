#include<bits/stdc++.h>
using namespace std;
//可以免费在最多种航线上搭乘飞机
//P4568 [JLOI2011]飞行路线
const int MAXN = 1e6 + 6;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x= (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, w, next;
    node(){}
    node(int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXN << 2];
int head[MAXN], dis[MAXN], inq[MAXN], cnt, minCost = 0x3f3f3f3f;
inline void add_edge(int from, int to, int w){
    Edge[cnt] = (node){to, w, head[from]};
    head[from] = cnt++;
}
int n , m, k, s, t;
inline void spfa(){
    memset(dis, 0x3f, sizeof(dis));
    deque<int>q;
    q.push_front(s), dis[s] = 0, inq[s] = true;
    while(!q.empty()){
        int cur = q.front();
        inq[cur] = false, q.pop_front();
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            if(dis[to] > dis[cur] + Edge[i].w){
                dis[to] = dis[cur] + Edge[i].w;
                if(!inq[to]){
                    if(q.empty()||dis[to] < dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
    for(int i = 0; i <= k; i++) minCost = min(minCost, dis[t + i * n]);
    cout << minCost;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int u, v, w;
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    s = read(), t = read();
    while(m -- ){
        u = read(), v = read(), w = read();
        for(int i = 0; i <= k; i++)
            add_edge(u + i * n, v + i * n, w), add_edge(v + i * n, u + i * n, w);
        for(int i = 0; i < k; i++)
            add_edge(u + i * n, v + (i + 1) * n, 0), add_edge(v + i * n, u + (i + 1) * n, 0);
    }
    spfa();
    return 0;
}