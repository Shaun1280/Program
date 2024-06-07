#include<bits/stdc++.h>
//CF1304D Shortest and Longest LIS
constexpr int MAXN = 2e5 + 5;
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int testCase, n, seq[MAXN]; 
string s;
int main() {
	std::ios::sync_with_stdio(false);
	cin >> testCase;
	while (testCase--) {
		cin >> n >> s;
		int num = n, last = 0;
		for (int i = 0; i < n; i++) {
			if (i == n - 1 || s[i] == '>') {
				for (int j = i; j >= last; j--) seq[j] = num--;
				last = i + 1;
			}
		}
		for (int i = 0; i < n; i++) 
			cout << seq[i] << (i == n - 1 ? '\n' : ' ');
		num = 1, last = 0;
		for (int i = 0; i < n; i++) {
			if(i == n - 1 || s[i] == '<') {
				for (int j = i; j >= last; j--) seq[j] = num++;
				last = i + 1;
			}
		}
		for (int i = 0; i < n; i++) 
			cout << seq[i] << (i == n - 1 ? '\n' : ' ');
	}
	return 0; 
}