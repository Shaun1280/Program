#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF1304F1
constexpr int MAXM = 2e4 + 4;
//https://codeforces.com/blog/entry/73934
using namespace std;
int n, m, k, animal[55][MAXM], dp[55][MAXM], sum[55][MAXM];//day i, put camera on pos j
int Lmax[55][MAXM], Rmax[55][MAXM];
inline int getSum(int t, int l, int r) {
	return sum[t][r] - sum[t][l - 1];
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> animal[i][j];
			sum[i][j] = sum[i][j - 1] + animal[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m - k + 1; j++) {
			int total = getSum(i, j, j + k - 1) + getSum(i + 1, j, j + k - 1);
			if (i == 1) {
				dp[i][j] = total;
				continue;
			}
			for (int x = max(1, j - k + 1); x <= min(m - k + 1, j + k - 1); x++) // minus intersection
				dp[i][j] = max(dp[i][j], dp[i - 1][x] + total - getSum(i, max(x, j), min(x + k - 1, j + k - 1))); 
			if (j > k) dp[i][j] = max(dp[i][j], Lmax[i - 1][j - k] + total); 
				//compare with Max prefix
			if (j + k <= m - k + 1) dp[i][j] = max(dp[i][j], Rmax[i - 1][j + k] + total); 
				//compare with Max suffix
		}
		for (int j = 1; j <= m - k + 1; j++) //getMax prefix
			Lmax[i][j] = max(Lmax[i][j - 1], dp[i][j]);
		for (int j = m - k + 1; j >= 1; j--) //getMax suffix
			Rmax[i][j] = max(Rmax[i][j + 1], dp[i][j]);	
	}
	cout << *max_element(dp[n] + 1, dp[n] + m + 1) << endl;
	return 0; 
}