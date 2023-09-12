#include<bits/stdc++.h>
const int MAXP = 1e5 + 5;
const int MAXE = 1e5 + 5;
typedef long long LL;
const LL Inf = 1e15;
using namespace std;
struct s{
    int to, next; LL w;
    s(){}
    s(int _to, LL _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXE];
struct node{
    LL dis; int p;//优先队列默认大顶堆
    //node a < node b   使得小的先出队列
    inline bool friend operator < (const node &a, const node &b){
        return a.dis > b.dis; 
    }
};
int head[MAXP], cnt, vis[MAXP];
LL HP[MAXP];
inline void add_edge(int from, int to, LL w){
    Edge[cnt] = (s){to, w, head[from]};
    head[from] = cnt++;
}
int n, m; 
LL k;
vector<LL>cost, C;
inline bool check(LL x){
    for(int i = 0; i < n; i++) HP[i] = Inf; HP[0] = 0LL;
    memset(vis, 0, sizeof(vis));
    priority_queue< node >q;
    q.push((node){HP[0], 0});
    while(!q.empty()){
        int cur = q.top().p;
        q.pop();
        if(vis[cur]) continue;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to;
            if(C[to] <= x && HP[to] > HP[cur] + Edge[i].w){
                HP[to] = HP[cur] + Edge[i].w;
                q.push((node){HP[to], to});
            }
        }
        vis[cur] = true;
    }
    if(HP[n - 1] < k) return true;
    return false;
}
inline void Binary_search(int l, int r){
    if(!check(Inf)){
        cout << "AFK";
        return;
    }
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(cost[mid])) r = mid - 1;//还存在更小答案
        else l = mid + 1;
    }
    cout << cost[l];
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> k;
    cost.resize(n), C.resize(n);
    for(int i = 0; i < n; i++) cin >> cost[i], C[i] = cost[i];
    sort(cost.begin(), cost.end());
    int u, v, w;
    while(m--){
        cin >> u >> v >> w;
        if(u == v) continue;
        add_edge(u - 1, v - 1, w), add_edge(v - 1, u - 1, w);
    }
    Binary_search(0, n - 1);
    return 0;
}