#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/cf11d-a-simple-task
const int MAXN = 20;
using namespace std;
int n, m, E[MAXN][MAXN];
long long dp[1 << MAXN][MAXN]; //点被经过对应二进制状态st, 处于i点
inline int read(){
    int x = 0;
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x;
}
inline int lowbit(int x) {
	for (int i = 0; i < n; i++) {
		if(x & (1 << i)) return i;
	}
	return 0;
}
int main(){
    n = read(), m = read();
    for(int i = 1; i <= m; i++){
		int u = read() - 1, v = read() - 1;
		E[u][v] = E[v][u] = 1;
	}
	long long ans = 0;
	for (int i = 0; i < n; i++) dp[1 << i][i] = 1; //以i为起点的环的个数
    for (int st = 1; st < (1 << n); st++)
        for (int i = 0; i < n; i++) { //i为当前点
			if (dp[st][i] == 0) continue;
			int lowest = lowbit(st);
			for (int j = lowest; j < n; j++) { //下一个要到达的点j 向后枚举点防止重复
				if (j == i || !E[i][j]) continue;
				if ((st & (1 << j)) == 0) //j未被访问过
					dp[st | (1 << j)][j] += dp[st][i];
				else if(j == lowest) ans += dp[st][i]; //j点已被访问过 出现环
			}       
		} 
    cout << (ans - m) / 2 << endl;
    return 0;
}