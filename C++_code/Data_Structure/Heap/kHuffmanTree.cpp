#include<bits/stdc++.h>
//huffman treeP2168 [NOI2015]荷马史诗
//https://www.luogu.com.cn/problem/P2168
constexpr int MAXN = 1e5 + 5;
constexpr int LOG = 18;
using namespace std;
using LL = long long;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct node {
	LL w, h; //height of node
	node(){}
	node(LL _w, LL _h) : w(_w), h (_h){}
	inline bool friend operator < (const node &a, const node &b) {
		return a.w == b.w ? a.h > b.h : a.w > b.w;
	}
};
priority_queue<node, vector<node>>q; 
LL n, k;
int main(){
	read(n), read(k);
	for (LL i = 1, tmp; i <= n; i++)
		read(tmp), q.push(node(tmp, 0));
	while ((n - 1) % (k - 1)) n++, q.push(node(0, 0));
	LL sum = 0;
	while (q.size() > 1) {
		LL num = 0, h = 0;
		for (int i = 1; i <= k; i++) {
			num += q.top().w;
			h = max(h, q.top().h);
			q.pop();
		}
		sum += num, q.push(node(num, h + 1));
	}
	cout << sum << endl << q.top().h << endl; 
	return 0;
}