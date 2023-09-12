#include<bits/stdc++.h>
//P1220 关路灯
//https://www.luogu.com.cn/problem/P1220
constexpr int MAXN = 55;
using namespace std;
int x[MAXN], P[MAXN], sum[MAXN];
int n, st, ans = 0x3f3f3f3f;
int dp[MAXN][MAXN][2]; //关闭了区间i, j 的最小耗量 0表示停留在左端点
int main() {
	std::ios::sync_with_stdio(false);
	cin >> n >> st;
	//memset(dp, 0x3f, sizeof(dp));
	for (int i = 1; i <= n; i++) 
		cin >> x[i] >> P[i], sum[i] = sum[i - 1] + P[i];
	for (int i = 1; i <= n; i++) dp[i][i][0] = dp[i][i][1] = sum[n] * abs(x[st] - x[i]);
	
	for (int len = 2; len <= n; len++) //区间dp枚举长度
		for (int i = 1; i <= n - len + 1; i++) {
			int j = i + len - 1;
			dp[i][j][0] = min(
				dp[i + 1][j][0] + abs(x[i + 1] - x[i]) * (sum[n] - (sum[j] - sum[i])),
				dp[i + 1][j][1] + abs(x[j] - x[i]) * (sum[n] - (sum[j] - sum[i]))
			);
			dp[i][j][1] = min(
				dp[i][j - 1][0] + abs(x[i] - x[j]) * (sum[n] - (sum[j - 1] - sum[i - 1])),
				dp[i][j - 1][1] + abs(x[j] - x[j - 1]) * (sum[n] - (sum[j - 1] - sum[i - 1]))
			);
		}
	cout << min(dp[1][n][0], dp[1][n][1]);
	return 0;
}