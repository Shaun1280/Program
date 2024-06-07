#include<bits/stdc++.h>
//P2868 [USACO07DEC]观光奶牛Sightseeing Cows
const int MAXP = 1e3 + 3;
const int MAXE = 6e3 + 3;
const double EPSILON = 1e-6;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch=getchar();
    while(!isdigit(ch)) f = (ch=='-')? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x<<3) + (x<<1) + ch -48, ch = getchar();
    return x * f; 
}
struct node{
    int to, next, t;
} Edge[MAXE];
int head[MAXP], fun[MAXP], vis[MAXP], cnt[MAXP]; 
double dis[MAXE];
int L, P, tot;
inline void add_edge(int from, int to, int t){
    Edge[tot].next = head[from];
    Edge[tot].to = to, Edge[tot].t = t;
    head[from] = tot++;
}
inline bool check(int s, double x){
    for(int i = 1; i <= L; i++) dis[i] = 1e9;
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    deque <int> q;
    q.push_front(s), vis[s] = true, dis[0] = .0;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        vis[cur] = false;//
        for(int i = head[cur]; i != -1; i = Edge[i].next){
            int to = Edge[i].to;
            if(dis[to] > dis[cur] + x * Edge[i].t - fun[to]){
                dis[to] = dis[cur] + x * Edge[i].t - fun[to];
                if(!vis[to]){
                    if(q.empty()||dis[to] < dis[q.front()]) q.push_front(to);
                        else q.push_back(to);//slf spfa
                    vis[to] = true; 
                    cnt[to] = cnt[cur] + 1; 
                    if(cnt[to] >= L) return true;
                }       
            }        
        }
    }
    return false;
}
inline void Binary_search(double l, double r){
    while(l + EPSILON < r){
        double mid = (l + r) / 2;
        if(check(0, mid)) l = mid;
        //sigma(x * t[i] - fun[i]) x[i] <0 (存在负环) 答案偏小
        else r = mid;
    }
    printf("%.2f", l);
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out","w", stdout);
    L = read(), P = read();
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= L; i++) fun[i] = read();
    int u, v, t;
    for(int i = 1; i <=P; i++){
        u = read(), v= read(), t = read();
        add_edge(u, v, t);
    }    
    for(int i = 1; i <= L; i++) add_edge(0, i, 0); //虚拟节点
    Binary_search(.0, 1e9);
    return 0;
}