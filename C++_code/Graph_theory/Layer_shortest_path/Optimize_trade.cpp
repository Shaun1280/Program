#include<bits/stdc++.h>
//P1073 最优贸易
//分层最短路
//tarjan + dp +tp
const int MAXM = 1e6 + 6;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, w, next;
    node(){}
    node(int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXM * 3];
int n, m, k, Max = -0x3f3f3f3f;
int tot, head[MAXM], inq[MAXM], dis[MAXM], val[MAXM];
inline void add_edge(int from, int to, int w){
    Edge[tot] = (node){to, w, head[from]};
    head[from] = tot++;
}
inline void add(int from, int to){
    add_edge(from, to, 0), add_edge(from + n, to + n, 0);
    add_edge(from + 2 * n, to + 2 * n, 0);
    add_edge(from, to + n, -val[from]);  //买了就得卖 卖放在第三层
    add_edge(from + n, to + 2 * n, val[from]);
}
inline void spfa(){
    for(int i = 1; i <= 3 * n + 5; i++) dis[i] = -0x3f3f3f3f;
    deque<int>q;
    q.push_back(1), inq[1] = true, dis[1] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            if(dis[to] < dis[cur] + Edge[i].w){
                dis[to] = dis[cur] + Edge[i].w;
                if(!inq[to]){
                    if(q.empty() || dis[to] > dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
    cout << dis[3 * n + 1];
}
int main(){
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for(int i = 1; i <= n; i++) val[i] = read();
    while(m--){
        int type, u, v;
        u = read(), v = read(), type = read();
        add(u, v);
        if(type == 2) add(v, u);//双向道路
    }
    add_edge(n, 3 * n + 1, 0), add_edge(n * 3, 3 * n + 1, 0);
    //最后一个点肯定不会买 对应2n
    spfa();
    return 0;
}