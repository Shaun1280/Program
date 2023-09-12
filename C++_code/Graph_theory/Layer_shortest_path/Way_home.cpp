#include<bits/stdc++.h>
const int MAXM = 1e6 + 6;
using namespace std;
//P3831 [SHOI2012]回家的路
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
struct s{
    int r, c;
    int pre;
};
vector<s>P;
inline bool cmp1(const s &a, const s &b){//row1 row2...
    if(a.r == b.r) return a.c < b.c;
    return a.r < b.r;
}
inline bool cmp2(const s &a, const s &b){//column1 column2...
    if(a.c == b.c) return a.r < b.r;
    return a.c < b.c;
}
int tot, head[MAXM], inq[MAXM];
int dis[MAXM];
inline void add_edge(int from, int to, int w){
    Edge[tot] = (node){to, w, head[from]};
    head[from] = tot++;
}
int n, m;
inline void spfa(){
    memset(dis, 0x3f, sizeof(dis));
    deque<int>q;
    q.push_back(0), inq[0] = true, dis[0] = 0;
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
    cout << (dis[m + 1] == 0x3f3f3f ? -1 : dis[m + 1]);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int sx, sy, tx, ty, r, c;
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    P.resize(m + 2);
    for(int i = 1; i <= m; i++)
        P[i].r = read(), P[i].c = read(), P[i].pre = i;
    P[0].r = read(), P[0].c = read(), P[0].pre = 0;
    P[m + 1].r = read(), P[m + 1].c = read(), P[m + 1].pre = m + 1;//terminal
    sort(P.begin(), P.end(), cmp1);
    for(int i = 1; i <= m + 1; i++)
        if(P[i].r == P[i - 1].r){
            int u = P[i].pre, v = P[i - 1].pre;
            //找到对应的初始下标
            add_edge(u, v, (P[i].c - P[i - 1].c) << 1),
            add_edge(v, u, (P[i].c - P[i - 1].c) << 1);
        }
    sort(P.begin(), P.end(), cmp2);
    for(int i = 1; i <= m + 1; i++)
        if(P[i].c == P[i - 1].c){
            int u = P[i].pre, v = P[i - 1].pre;
            add_edge(u + m + 2, v + m + 2, (P[i].r - P[i - 1].r) << 1),
            add_edge(v + m + 2, u + m + 2, (P[i].r - P[i - 1].r) << 1);
        }     
    for(int i = 1; i <= m; i++)//对应层间 初始下标连边
        add_edge(i, i + m + 2, 1), add_edge(i + m + 2, i, 1);
    //起点终点连0边
    add_edge(0, m + 2, 0), add_edge(m + 2, 0, 0);
    add_edge(m + 1, 2 * m + 3, 0), add_edge(2 * m + 3, m + 1, 0);
    spfa();
    return 0;
}