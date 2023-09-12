#include<bits/stdc++.h>
typedef long long LL;
/*longest path*/
const LL Inf = 1e15;
const int MAXN = 1e5 + 5;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, next;
    LL w;
    node(){}
    node(int _to, LL _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXN * 3];
int tot, head[MAXN], inq[MAXN], cnt[MAXN];
LL dis[MAXN];
inline void add_edge(int from, int to, LL w){
    Edge[tot] = (node){to, w, head[from]};
    head[from] = tot++;
}
int n, k, x;
LL total;
inline bool spfa(){
    deque<int>q;
    for(int i = 1; i <= n; i++)
        q.push_back(i), inq[i] = true, dis[i] = 1LL;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            if(dis[to] < dis[cur] + Edge[i].w){
                dis[to] = dis[cur] + Edge[i].w;
                if(!inq[to]){
                    if(q.empty() || dis[to]  >/*@*/ dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                    cnt[to] = cnt[cur] + 1;
                    if(cnt[to] > n) return true;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) total += dis[i];
    return false;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    n = read(), k = read();
    memset(head, -1, sizeof(head));
    int a, b;
    while(k--){
        x = read(), a = read(), b = read();
        switch (x){
        case 1: 
            add_edge(a, b, 0LL), add_edge(b, a, 0LL); break;
        case 2: 
            add_edge(a, b, 1LL); break;
        case 3: 
            add_edge(b, a, 0LL); break;
        case 4: 
            add_edge(b, a, 1LL); break;
        case 5: 
            add_edge(a, b, 0LL); break;
        }
    }
    cout << (spfa() ? -1 : total);
    return 0;
}