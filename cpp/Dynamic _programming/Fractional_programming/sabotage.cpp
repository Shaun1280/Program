#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
const double EPSILON = 1e-5;
//https://www.luogu.com.cn/blog/user49440/ti-xie-p2115-po-huai
//https://www.luogu.com.cn/problem/P2115
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, milk[MAXN];
double p[MAXN], sum[MAXN], Max[MAXN], Min[MAXN], ans;
inline bool check(double x){
	for(int i = 1; i <= n; i++) p[i] = sum[i] - x * i;
	Max[n - 1] = p[n - 1], Min[1] = p[1];
	for(int i = n - 2; i >= 2; i--) Max[i] = fmax(Max[i + 1], p[i]);
	for(int i = 2; i <= n - 1; i++) Min[i] = fmin(Min[i - 1], p[i]);
	for(int i = 2; i <= n - 1; i++) 
		if(Max[i] - Min[i - 1] >= p[n]) return true;
	return false;
}
int main(){
	n = read();
	for(int i = 1; i <= n; i++) milk[i] = read(), sum[i] = sum[i - 1] + milk[i];
	double l = 0, r = 1e9;
	while(l + EPSILON < r){
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.3f", l);
	return 0;
}