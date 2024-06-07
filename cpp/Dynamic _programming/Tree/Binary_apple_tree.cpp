#include <bits/stdc++.h>
const int MAXN = 1e2 + 2;
#define pii pair<int, int>
//https://www.luogu.com.cn/blog/user48611/p2015-er-cha-peng-guo-shu
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
vector<vector<pii>> E;
int n, m;
int dp[MAXN][MAXN], sz[MAXN]; //cur的子树保留i条边
void dfs(int cur, int fa) {
	for (auto i : E[cur]) {
		int to = i.first, w = i.second;
		if (to == fa) continue;
		dfs(to, cur), sz[cur] += sz[to];
		for(int i = min(sz[cur], m); i >= 0; i--)
			for(int j = min(sz[to], i - 1); j >= 0; j--)
				dp[cur][i] = max(dp[cur][i], dp[to][j] + dp[cur][i - 1 - j] + w);
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin >> n >> m;
	E.resize(n + 1);
	for(int i = 1; i <= n; i++) sz[i] = 1;
	for (int i = 1; i < n; i++)	{
		int u = read(), v = read(), w = read();
		E[u].push_back(make_pair(v, w)), E[v].push_back(make_pair(u, w));
	}
	dfs(1, 0);
	cout << dp[1][m];
	return 0;
}