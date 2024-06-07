#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2756
constexpr int MAXN = 1e2 + 2;
constexpr int Inf = 0x3f3f3f3f;
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct node{
	int to, c, next;
	node(){}
	node(int _to, int _c, int _next){
		to = _to, c = _c, next = _next;
	}
};
vector<node>Edge;
int head[MAXN], curv[MAXN], depth[MAXN], inq[MAXN], tot;
inline void add(int from, int to, int c){
	Edge.push_back(node(to, c, head[from])), head[from] = tot++;
	Edge.push_back(node(from, 0, head[to])), head[to] = tot++;
}
int n, m, s, t;
inline bool bfs(){
	memset(inq, 0, sizeof(inq));
	memset(depth, 0, sizeof(depth));
	memcpy(curv, head, sizeof(head));
	queue<int>q;
	q.push(s), depth[s] = 1;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		inq[cur] = false;
		for(int i = head[cur]; ~i; i = Edge[i].next){
			int to = Edge[i].to;
			if(!Edge[i].c || depth[to]) continue;
			depth[to] = depth[cur] + 1;
			if(!inq[to]) q.push(to), inq[to] = true;
		}
	}
	return depth[t];
}
int dinic(int cur, int flow){
	if(cur == t) return flow;
	int rest = flow;
	for(int i = curv[cur]; ~i; i = Edge[i].next){
		curv[cur] = i;
		int to = Edge[i].to;
		if(Edge[i].c && depth[to] == depth[cur] + 1){
			int k = dinic(to, min(Edge[i].c, rest));
			if(k == 0) depth[to] = 0;
			Edge[i].c -= k;
			Edge[i ^ 1].c += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int main(){
	m = read(), n = read();
	//外籍 皇家空军
	memset(head, -1, sizeof(head));
	s = 0, t = n + 1;
	int u, v;
	while(cin >> u >> v && (u != -1) && (v != -1)){
		add(u, v, Inf);
	}
	for(int i = 1; i <= m; i++) add(s, i, 1);
	for(int i = m + 1; i <= n; i++) add(i, t, 1);
	int maxFlow(0), flow(0);
	while(bfs()){
		while(flow = dinic(s, Inf)) maxFlow += flow;
	}
	if(maxFlow == 0){
		puts("No Solution!");
		return 0;
	}
	printf("%d\n", maxFlow);
	for(int i = 0; i < Edge.size(); i += 2){
		if(Edge[i].to == s || Edge[i ^ 1].to == s) continue;
		if(Edge[i].to == t || Edge[i ^ 1].to == t) continue;
		if(Edge[i ^ 1].c)
			printf("%d %d\n", Edge[i ^ 1].to, Edge[i].to);
	}
	return 0;
}