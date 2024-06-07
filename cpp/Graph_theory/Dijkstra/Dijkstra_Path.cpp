#include<bits/stdc++.h>
const int MAXN = 2e5+1;
#define LL long long
const LL Inf = 1ll<<44;
using namespace std;
struct e{
    int next, to;
    LL dis;
} *Edge;
struct node{
    LL dis;
    int pos;
    inline bool operator < (const node &N)const{
        return N.dis < dis;
    }
};
int N, M, cnt;
int head[MAXN], vis[MAXN], Pre[MAXN];
LL dis[MAXN];
inline void add_edge(int from, int to, LL dis){
    Edge[cnt].next = head[from];
    Edge[cnt].to = to, Edge[cnt].dis = dis;
    head[from] = cnt++;
}
inline void Init(){
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(Pre, 0, sizeof(Pre));
    for(int i = 0; i <= N; i++) dis[i] = Inf;
}
inline void dijkstra(){
    vector <int> Path;
    priority_queue< node > q;
    q.push( (node){dis[1] = 0ll, 1});
    while(!q.empty()){
        int cur = q.top().pos;
        q.pop();
        if( vis[cur] ) continue;
        for(int i = head[cur]; i != -1; i = Edge[i].next){
            int go = Edge[i].to;
            if(dis[go] > dis[cur] + Edge[i].dis){
                dis[go] = dis[cur] + Edge[i].dis;
                q.push( (node){dis[go], go});
                Pre[go] = cur;
            }
        } 
        vis[cur] = 1;
    }
    if(!vis[N]) printf("-1");
    else{
        for(int i = N; i; i = Pre[i])  Path.push_back(i);
        while(! Path.empty()){
            printf("%d ", Path.back());
            Path.pop_back();
        }
    }
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin >> N >> M;
    Edge = (e *)malloc(2 * (M + 2) * sizeof(e));
    Init();
    while(M--){
        int from, to; LL dis;
        cin >> from >> to >> dis;
        add_edge(from, to , dis);
        add_edge(to, from, dis);
    }
    dijkstra();
    free(Edge);
    return 0;
}