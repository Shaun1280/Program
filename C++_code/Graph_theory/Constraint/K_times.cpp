#include<bits/stdc++.h>
//P4926 [1007]倍杀测量者
const double Inf = 1e9 + 1;
const double EPSILON = 1e-6;
const int MAXN = 1e3 + 3;
const int MAXE = 3e3 + 3;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, next, opt;
    double k;
    node (){}
    node (int _to, double _k, int _next, int _opt){
        to = _to, k = _k, next = _next, opt = _opt;
    }
}Edge[MAXE];
int n, s, t, tot, head[MAXN], Cnt[MAXN], inq[MAXN];
inline void add_edge(int from, int to, double k, int opt){
    Edge[tot] = node(to, k, head[from], opt);
    head[from] = tot++;
}
double dis[MAXN];
inline bool check(double t){
    deque<int>q;
    for(int i = 1; i <=n; i++) dis[i] = Inf;
    memset(Cnt, 0, sizeof(Cnt)), memset(inq, 0, sizeof(inq));
    q.push_front(0), inq[0] = true;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front(), inq[cur] = false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            double w;
            if(Edge[i].opt == 0) w = Edge[i].k;
            if(Edge[i].opt == 1 && Edge[i].k - t <= 0) return false;//t偏大 r = mid
            if(Edge[i].opt == 1) w = - log2(Edge[i].k - t);
            if(Edge[i].opt == 2) w = log2(Edge[i].k + t);
            if(dis[to] > dis[cur] + w){
                dis[to] = dis[cur] + w;
                if(!inq[to]){
                    if(q.empty() || dis[to] < dis[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    Cnt[to] = Cnt[cur] + 1;
                    if(Cnt[to] > n) return true;
                }
            }
        }
    }
    return false;
}
inline void Binary_search(double l, double r){
    while(l + EPSILON < r){
        double mid = (l + r) / 2.;
        if(check(mid)) l = mid; //单调 二分查找
        else r = mid;
    }
    if(l == 0.0) printf("-1"); 
    else printf("%.5f", l);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    n = read(), s = read(), t = read();
    memset(head, -1, sizeof(head));
    int opt, u, v, k , r = Inf;
    for(int i = 1; i <= s; i++){
        opt = read(), u = read(), v = read(), k = read();
        r = min (r, k);
        add_edge(u, v, k, opt);
    }
    for(int i = 1; i <= t; i++)
        cin >> u >> k, add_edge(0, u, log2(k), 0), add_edge(u, 0, -log2(k), 0);//建双向边
    Binary_search(0., 2.0 * r);
    return 0;
}