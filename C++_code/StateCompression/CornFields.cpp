#include<bits/stdc++.h>
const int MAXN = 13;
//https://www.luogu.com.cn/problem/P1879
const int M = 1e9;
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int m, n, ans;
int field[MAXN];
vector<vector<int>>state;
int dp[MAXN][1 << 12];
inline void Init(){
	for(int i = 1; i <= m; i++)
		for(int st = 0; st < (1 << n); st++){
			if((st & (st >> 1)) || (st & (st << 1))) continue;
			if((st | field[i]) != field[i]) continue;
			state[i].push_back(st);
		}
	for(auto i : state[1]){
		dp[1][i] = 1;
		if(m == 1) ans = (ans + dp[1][i]) % M;
	}
	for(int i = 2; i <= m; i++){
		for(auto s1 : state[i]){
			for(auto s2 : state[i - 1]){
				if(s1 & s2) continue;
				dp[i][s1] = (dp[i][s1] + dp[i - 1][s2]) % M;
			}
			if(i == m) ans = (ans + dp[i][s1]) % M;
		}
	}
	cout << ans << endl;
}
int main(){
	m = read(), n = read();
	state.resize(m + 1);
	for(int i = 1; i <= m; i++)
		for(int j = n - 1; j >= 0; j--){
			int tmp = read();
			field[i] += (tmp << j);
		}
	Init();
	return 0;
}