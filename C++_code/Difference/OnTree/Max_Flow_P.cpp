#include<bits/stdc++.h>
//P3128 [USACO15DEC]Max Flow P
//difference on tree
#define pii pair<int, int> 
constexpr int MAXN = 5e4 + 4;
constexpr int LOG = 17;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
int n, m, f[MAXN][LOG], depth[MAXN], delta[MAXN], ans;
vector<int> G[MAXN];
inline void dfs(int cur, int fa) {
	depth[cur] = depth[fa] + 1, f[cur][0] = fa;
	for (int i = 1; i < LOG; i++) f[cur][i] = f[f[cur][i - 1]][i - 1];
	for (auto to : G[cur]) {
		if (fa == to) continue;
		dfs(to, cur);
	}
}
inline int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (int i = LOG - 1; i >= 0; i--) 
		if (depth[f[u][i]] >= depth[v])
			u = f[u][i];
	if (u == v) return u;
	for (int i = LOG - 1; i >= 0; i--) 
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}
inline int dfs2(int cur, int fa) {
	int cnt = 0;
	for (auto to : G[cur]) {
		if (to == fa) continue;
		cnt += dfs2(to, cur);
	}
	ans = max(ans, cnt + delta[cur]);
	return cnt + delta[cur];
}
int main(){
	freopen("test.in", "r", stdin);
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, G[u].emplace_back(v), G[v].emplace_back(u);
	dfs(1, 0);
	for (int i = 1, u, v, lca; i <= m; i++) {
		cin >> u >> v, lca = LCA(u, v);
		delta[u]++, delta[v]++, delta[lca]--, delta[f[lca][0]]--;
	}
	ans = max(ans, dfs2(1, 0));
	cout << ans << endl;
	return 0;
}