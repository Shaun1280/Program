#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/uva10816-travel-in-desert
//uva Travel in desert
constexpr int MAXN = 2e2 + 2;
constexpr int MAXE = 1e4 + 4;
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, m, s, t;
struct E {	
	int from, to;
	double r, d;
	inline friend bool operator < (const E &a, const E &b) {
		return a.r < b.r;
	}
}tmp;// temperature & disance
vector<E>vec;
int head[MAXN], tot, pre[MAXN], inq[MAXN], fa[MAXN];
double dis[MAXN];
struct node{
	int to, next;
	double d;
	node(){}
	node(int _to, double _d, int _next){
		to = _to, d = _d, next = _next;
	}
}Edge[MAXE << 1];
inline void add(int from, int to, double d) {
	Edge[tot] = node(to, d, head[from]), head[from] = tot++;
	Edge[tot] = node(from, d, head[to]), head[to] = tot++;
}
inline void Init() {
	s = read(), t = read(), tot = 0;
	memset(head, -1, sizeof(head)), memset(inq, 0, sizeof(inq));
	memset(Edge, 0, sizeof(Edge)), memset(pre, 0, sizeof(pre));
	vec.clear();
	for (int i = 1; i <= n; i++) fa[i] = i, dis[i] = 1e9;
	for (int i = 1; i <= m; i++) {
		tmp.from = read(), tmp.to = read(), scanf("%lf%lf", &tmp.r, &tmp.d);
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end());
}
inline int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
double minDis, maxHeat;
inline void kruskal() {
	for (int i = 0; i < vec.size(); i++) {
		int from = vec[i].from, to = vec[i].to;
		int r1 = find(from), r2 = find(to);
		if (r1 == r2) continue;
		fa[r1] = r2;
		if (find(s) == find(t)) {
			maxHeat = vec[i].r;
			break;
		}
	}
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].r <= maxHeat)
			add(vec[i].from, vec[i].to, vec[i].d);
}
inline void spfa() {
	deque<int>q;
	q.push_front(s), dis[s] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop_front();
		inq[cur] = false;
		for (int i = head[cur]; ~i; i = Edge[i].next) {
			int to = Edge[i].to;
			if (dis[to] > dis[cur] + Edge[i].d) {
				dis[to] = dis[cur] + Edge[i].d;
				pre[to] = cur;
				if (!inq[to]) {
					if (q.empty() || dis[to] < dis[q.front()]) q.push_front(to);
					else q.push_back(to);
					inq[to] = true;
				}
			}
		}
	}
}
inline void print_path(int cur) {
	if (cur != s) print_path(pre[cur]);
	if (cur == t) printf("%d\n", cur);
	else printf("%d ", cur);
}
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		Init();
		kruskal();
		spfa();
		print_path(t);
		printf("%.1f %.1f\n", dis[t], maxHeat);
	}
	return 0;
}