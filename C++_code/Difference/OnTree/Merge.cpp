#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/p4556-vani-you-yue-kuai-yu-tian-di-wei-ba
//P4556 [Vani有约会]雨天的尾巴 /【模板】线段树合并
constexpr int MAXN = 1e5 + 5;
constexpr int LOG = 17;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Node {
	Node *lson, *rson;
	int cnt, pos;
}Tree[MAXN * LOG * 4], *root[MAXN];
#define Lson root->lson
#define Rson root->rson
vector<vector<int> > G;
int tot, n, m, f[MAXN][LOG], depth[MAXN], ans[MAXN], lim;
inline Node * newNode(Node * &root) { 
	if (root == NULL) root = &Tree[++tot];
	return root;
}
inline void update(Node *root) {
    int Lcnt = Lson == NULL ? 0 : Lson->cnt, Rcnt = Rson == NULL ? 0 : Rson->cnt;
    int Lpos = Lson == NULL ? 0 : Lson->pos, Rpos = Rson == NULL ? 0 : Rson->pos;
	root->cnt = max(Lcnt, Rcnt);
	root->pos = (Lcnt >= Rcnt) ? Lpos : Rpos;
}
inline void insert(Node *root, int L, int R, int val, int delta) {
	if (L == R) {
		root->cnt += delta;
		root->pos = root->cnt ? L : 0;
		return;
	}
	int mid = (L + R) >> 1;
	if (val <= mid) insert(newNode(Lson), L, mid, val, delta);
	else insert(newNode(Rson), mid + 1, R, val, delta);
	update(root);
}
/*
inline Node * merge(Node *root, Node *pre, int L, int R) {
	if (root == NULL || root == Tree) return pre;
	if (pre == NULL || pre == Tree) return root;
	if (L == R) {
		root->cnt += pre->cnt;
		root->pos = root->cnt ? L : 0;
		return root;
	}
	int mid = (L + R) >> 1;
	Lson = merge(Lson, pre->lson, L, mid);
	Rson = merge(Rson, pre->rson, mid + 1, R);
	update(root);
	return root;
}*/
inline void merge(Node *&root, Node *pre, int L, int R) {
	if (root == NULL) {root = pre; return;}
	if (pre == NULL) return;
	if (L == R) {
		root->cnt += pre->cnt;
		root->pos = root->cnt ? L : 0;
        return;
	}
	int mid = (L + R) >> 1;
	merge(Lson, pre->lson, L, mid);
	merge(Rson, pre->rson, mid + 1, R);
	update(root);
}
inline void dfs(int cur, int fa) {
	depth[cur] = depth[fa] + 1, f[cur][0] = fa;
	for (int i = 1; i < LOG; i++) f[cur][i] = f[f[cur][i - 1]][i - 1];
	for (auto to : G[cur]) {
		if (to == fa) continue;
		dfs(to, cur);
	}
}
inline void dfs2(int cur, int fa) {
	for (auto to : G[cur]) {
		if (to == fa) continue;
		dfs2(to, cur);
		merge(root[cur], root[to], 1, MAXN - 5);
	}
	ans[cur] = root[cur]->pos;
}
inline int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (int i = LOG - 1; i >= 0; i--)
		if (depth[f[u][i]] >= depth[v]) u = f[u][i];
	if (u == v) return u;
	for (int i = LOG - 1; i >= 0; i--)
		if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}
int main(){
	read(n), read(m), G.resize(n + 1);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		G[u].push_back(v), G[v].push_back(u); 
	}
	for (int i = 0; i <= n; i++) newNode(root[i]);
	dfs(1, 0);
	for (int i = 1, u, v, z, lca; i <= m; i++) {
		read(u), read(v), read(z), lca = LCA(u, v);
		insert(root[u], 1, MAXN - 5, z, 1);
		insert(root[v], 1, MAXN - 5, z, 1);
		insert(root[lca], 1, MAXN - 5, z, -1);
		insert(root[f[lca][0]], 1, MAXN - 5, z, -1);
	}
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}