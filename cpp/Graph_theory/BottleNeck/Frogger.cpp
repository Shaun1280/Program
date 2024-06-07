#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/uva534-frogger
constexpr int MAXM = 1e5 + 5;
constexpr int MAXN = 2e2 + 2;
using namespace std;
int n, x[MAXN], y[MAXN], fa[MAXN];
struct node{
    int from, to, next, id;
    double w;
    node(){}
    node(int _from, int _to, int _id, int _next, double _w){
        from = _from, to = _to, id = _id, next = _next, w = _w;
    }
}Edge[MAXM];
int head[MAXN], tot, inTree[MAXM];
double dis[MAXN];
inline int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void Union(int a, int b){
    int r1 = find(a), r2 = find(b);
    if(r1 != r2) fa[r1] = r2;
}
inline void add(int from, int to, double w){
    Edge[tot] = node(from, to, tot, head[from], w), head[from] = tot++;
    Edge[tot] = node(to, from, tot, head[to], w), head[to] = tot++;
}
inline void Init(){
    tot = 0;
    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <= n; j++){
            double dis = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
            add(i, j, dis);
        }
}
inline bool cmpw(const node &a, const node &b){
    return a.w < b.w;
}
inline bool cmpid(const node &a, const node &b){
    return a.id < b.id;
}
inline void kruskal(){
    sort(Edge, Edge + tot, cmpw);
    for(int i = 0, cnt = 0; i < tot; i++){
        int from = Edge[i].from, to = Edge[i].to;
        if(find(from) != find(to)){
            Union(from, to);
            cnt++;
            inTree[Edge[i].id] = inTree[Edge[i].id ^ 1] = true;
        }
        if(cnt == n - 1) break;
    }
    sort(Edge, Edge + tot, cmpid);
}
void dfs(int cur, int fa){
    for(int i = head[cur]; ~i; i = Edge[i].next){
        if(!inTree[i]) continue;
        int to = Edge[i].to;
        if(fa == to) continue;
        dis[to] = max(dis[cur], Edge[i].w);
        dfs(to, cur);
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    int testCase(0);
    while(cin >> n && n){
        testCase++;
        memset(inTree, 0, sizeof(inTree));
        memset(head, -1, sizeof(head));
        memset(Edge, 0, sizeof(Edge));
        for(int i = 1; i <= n; i++){
            cin >> x[i] >> y[i]; 
            fa[i] = i, dis[i] = 0;
        }
        Init();
        kruskal();
        dfs(1, 0);
        cout << "Scenario #" << testCase << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << dis[2] << endl; //#include<iomanip>
        cout << endl;
    }
    return 0;
}