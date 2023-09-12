#include<bits/stdc++.h>
#define LL long long
const int MAXE = 1e6 + 1;
const int MAXP = 1e3 + 1;
const LL Inf = 1LL << 50;
using namespace std;
inline LL read(){
    LL x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, w, next;
    node (){}
    node (int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXE];
int n, Ml, Md, cnt, head[MAXP];
inline void add_edge(int from, int to, int w){
    Edge[cnt] = node(to, w, head[from]);
    head[from] = cnt++;
}
LL dis[MAXP];
int inq[MAXP], Cnt[MAXP];
inline bool spfa(int s){
    deque <int> q;
    memset(inq, 0, sizeof(inq));
    memset(Cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++) dis[i] = Inf;
    q.push_front(s), inq[s] = true, dis[s] = 0;
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
                    Cnt[to] = Cnt[cur] + 1;
                    if(Cnt[to] > n) return false;
                }
            }
        }
    }
    return true;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    n = read(), Ml = read(), Md = read();
    memset(head, -1, sizeof(head));
    int a, b, d;
    for(int i = 1; i <= Ml; i++)
        a = read(), b = read(), d = read(), 
        add_edge(a, b, d);
    for(int i = 1; i <= Md; i++)
        a = read(), b = read(), d = read(),
        add_edge(b, a, -d);
    for(int i = 1; i <= n; i++) add_edge(0, i, 0);
    if(!spfa(0)) {
        printf("-1"); 
        return 0;
    }
    spfa(1);
    cout << (dis[n] == Inf ? -2 : dis[n]);
    return 0;
}