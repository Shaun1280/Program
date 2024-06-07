#include<bits/stdc++.h>
/*
*账时需要从转账金额里扣除百分之几的手续费，
*请问A最少需要多少钱使得转账后B收到100元。
*O(m+n)log2n
*/
const int MAXP=2001;
const int MAXE=1e5+1;
using namespace std;
struct s{
    int next, to;
    double dis;
}Edge[MAXE<<1];
int head[MAXP], cnt; 
inline void Add_edge(int from, int to, int dis){
    Edge[cnt].next=head[from]; //an edge from head[from]
    Edge[cnt].to=to;
    Edge[cnt].dis=1.0-0.01*dis;
    head[from]=cnt++;
}
struct Node{
    double dis;
    int P;
    inline bool operator <(const Node &N)const{
        return N.dis > dis;
    }
};
int n, m, start, End, vis[MAXP];
double dis[MAXP];
inline void Init(){
    for(int i=1; i<=n; i++) dis[i]=.0;
    dis[start]=1.0;
}
inline void dijkstra(){
    priority_queue< Node/*storage method*/ >q;
    q.push((Node) {1.0, start});
    while(!q.empty()){
        int now=q.top().P;
        q.pop();
        if(vis[now]) continue;
        for(int i=head[now]; i!=-1; i=Edge[i].next){
            int go=Edge[i].to;
            if( dis[go] < dis[now] * Edge[i].dis){
                dis[go] = dis[now] * Edge[i].dis;
                q.push((Node) {dis[go], go});
            }
        }
        vis[now]=1;
    }
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out","w",stdout);
    scanf("%d%d",&n,&m);
    memset(head, -1, sizeof(head));
	for(int i=1; i<=m; i++) {
		int from,to,d;
		scanf("%d%d%d",&from,&to,&d);
		Add_edge(from,to,d);
        Add_edge(to,from,d);
	}  
    scanf("%d%d",&start, &End);
    Init();
	dijkstra();
    printf("%.8lf", 100/dis[End]);
    return 0;
}