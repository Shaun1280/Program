#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1251
constexpr int MAXN = 4e3 + 6;
constexpr long long Inf = 0x3f3f3f3f3f3f3f3f;
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct node {
	int to, c, w, next;
	node(){}
	node(int _to, int _c, int _w, int _next) : to(_to), c(_c), w(_w), next(_next) {}
}Edge[MAXN << 4];
long long p, m, f, n, s; // n > m, s < f
int N, tot, st, ed;
array<long long, MAXN>head, curv, vis, inq, cost, napkin;
inline void add(int from, int to, long long c, int w) {
	Edge[tot] = node(to, c, w, head[from]), head[from] = tot++;
	Edge[tot] = node(from, 0, -w, head[to]), head[to] = tot++;
}
inline bool BFS() {
	memset(&cost, 0x3f, sizeof(cost)), memset(&inq, 0, sizeof(inq));
	memcpy(&curv, &head, sizeof(head));
	queue<int>q;
	q.push(st), cost[st] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop(), inq[cur] = false;
		for (int i = head[cur]; ~i; i = Edge[i].next) {
			int to = Edge[i].to, w = Edge[i].w;
			if (cost[to] > cost[cur] + w && Edge[i].c) {
				cost[to] = cost[cur] + w;
				if (!inq[to]) q.push(to), inq[to] = true;
			}
		}
	}
	return !(cost[ed] == Inf);
}
inline int dinic(int cur, long long limit) {
	if (!limit || cur == ed) return limit;
	int flow = 0;
	vis[cur] = true;
	for (int i = curv[cur]; ~i; i = Edge[i].next) {
		int to = Edge[i].to, w = Edge[i].w;
		if(!vis[to] && Edge[i].c && cost[to] == cost[cur] + w) {
			curv[cur] = i;
			int k = dinic(to, min(limit, 1LL * Edge[i].c));
			if(k == 0) continue;
			Edge[i].c -= k, Edge[i ^ 1].c += k;
			limit -= k, flow += k;
		}
	}
	vis[cur] = false;
	if(flow == 0) cost[cur] = Inf;
	return flow;
}
int main() {
	memset(&head, -1, sizeof(head));
	N = read();
	st = 0, ed = 2 * N + 1;
	for (int i = 1; i <= N; i++) {
		napkin[i] = read();
		add(st, i + N, napkin[i], 0), add(i, ed, napkin[i], 0); 
		//当天结束需要送洗的纸巾  当天流入的纸巾流向汇点
	}
	p = read(), m = read(), f = read(), n = read(), s = read();
	for (int i = 1; i <= N; i++) {
		add(st, i, Inf, p); //当日起始点购买新的餐巾 
		if (i + 1 <= N) add(i + N, i + N + 1, Inf, 0); //延期送洗 当天结束点连向下一天结束点
		if (i + m <= N) add(i + N, i + m, Inf, f); //当日送洗 当天结束点连向m天后开始点
		if (i + n <= N) add(i + N, i + n, Inf, s); //当日送洗 当天结束点连向n天后开始点
	}
	long long minCost(0);
	while (BFS()) {
		int flow = dinic(st, Inf);
		minCost += cost[ed] * flow;
	}
	cout << minCost << endl;
	return 0;
}