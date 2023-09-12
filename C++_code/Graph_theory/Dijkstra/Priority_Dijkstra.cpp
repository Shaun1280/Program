#include<bits/stdc++.h>
/*get the dis of every point*/
/*O(m+n)log2n*/
#define Inf 0x7fffffff
const int MAXP=1e6+1;
const int MAXE=2e6+1;
using namespace std;
struct s{
    int next, to, dis;
}Edge[MAXE];
int head[MAXP], cnt; 
inline void Add_edge(int from, int to, int dis){
    Edge[cnt].next=head[from]; //an edge from head[from]
    Edge[cnt].to=to, Edge[cnt].dis=dis;
    head[from]=cnt++;
}
struct Node{
    int dis, P;
    inline bool operator <(const Node &N)const{
        return N.dis < dis;
    }
};
int n,m,start,vis[MAXP],dis[MAXP];
inline void Init(){
    memset(head, -1, sizeof(head));
    for(int i=1; i<=n; i++) dis[i]=Inf;
    dis[start]=0;
}
inline void dijkstra(){
    priority_queue< Node/*storage method*/ >q;
    q.push((Node) {0, start});
    while(!q.empty()){
        int now=q.top().P;
        q.pop();
        if(vis[now]) continue;
        for(int i=head[now]; i!=-1; i=Edge[i].next){
            int go=Edge[i].to;
            if( dis[go] > dis[now] + Edge[i].dis){
                dis[go] = dis[now] + Edge[i].dis;
                q.push((Node) {dis[go], go});
            }
        }
        vis[now]=1;
    }
    for(int i=1; i<=n; i++) printf("%d ",dis[i]);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out","w",stdout);
    scanf("%d%d%d",&n,&m,&start);
	Init();
	for(int i=1; i<=m; i++) {
		int from,to,dis;
		scanf("%d%d%d",&from,&to,&dis);
		Add_edge(from,to,dis);
	}
	dijkstra();
    return 0;
}