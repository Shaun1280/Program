#include<bits/stdc++.h>
//P2498 [SDOI2012]拯救小云公主
constexpr int MAXN = 3e3 + 3;
constexpr double EPSILON = 1e-8;
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, row, line, vis[MAXN];
array<double, MAXN> x, y, dis[MAXN];
inline bool check(double r) {
	memset(&vis, 0, sizeof(vis));
	queue<int>q;
	for (int i = 1; i <= n; i++) 
		if(y[i] - r <= 1 || row - x[i] <= r) q.push(i), vis[i] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (line - y[cur] <= r || x[cur] - r <= 1) return false;
		for (int i = 1; i <= n; i++)
			if (!vis[i] && dis[cur][i] <= 4 * r * r)  q.push(i), vis[i] = true;
	}
	return true;
}
int main() {
	n = read(), row = read(), line = read();
	for (int i = 1; i <= n; i++) x[i] = read(), y[i] = read();
	for (int i = 1; i < n; i++) 
		for (int j = i + 1; j <= n; j++) 
			dis[i][j] = dis[j][i] = pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2);
	double l = 0, r = max(1.0 * row, 1.0 * line), ans;
	while (l + EPSILON < r) {
		double mid = (l + r) / 2;
		if(check(mid)) l = mid, ans = mid;
		else r = mid;
	}
	printf("%.2f", ans);
	return 0;
}