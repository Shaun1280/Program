#include<bits/stdc++.h>
const int MAXM = 1e6 + 6;
//P4822 [BJWC2012]冻结 k条路的权值能变为1/2
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
}Edge[MAXM];
int tot, head[MAXM], inq[MAXM], dis[MAXM];
inline void add_edge(int from, int to, int w){
    Edge[tot] = (node){to, w, head[from]};
    head[from] = tot++;
}
int n, m, k, Min = 0x3f3f3f3f;
inline void spfa(){
    memset(dis, 0x3f, sizeof(dis));
    deque<int>q;
    q.push_back(1), inq[1] = true, dis[1] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            if(dis[to] > dis[cur] + Edge[i].w){
                dis[to] = dis[cur] + Edge[i].w;
                if(!inq[to]){
                    if(q.empty() || dis[to] < dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
    for(int j = 0; j <=k; j++)
        Min = min(Min, dis[n + j * n]);
    cout << Min;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    while(m--){
        int u, v, w;
        u = read(), v = read(), w = read();
        for(int j = 0; j <= k; j++)
            add_edge(u + j * n, v + j * n, w), add_edge(v + j * n, u + j * n, w);
        for(int j = 0; j < k; j++)
            add_edge(u + j * n, v + (j + 1) * n, w >> 1), add_edge(v + j * n, u + (j + 1) * n, w >> 1);
    }
    spfa();
    return 0;
}