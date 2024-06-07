#include<bits/stdc++.h>
constexpr int MAXN = 4e4 + 4;
//P3097 [USACO13DEC]最优挤奶Optimal Milking
//https://www.luogu.com.cn/blog/user48611/p3097-usaco13dec-zui-you-ji-nai-optimal-milking
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct segTree {
	#define LL long long 
	int l, r; LL f[2][2];
}Tr[MAXN << 4];
int n, d, milk[MAXN];
#define Lnode (node << 1)
#define Rnode (node << 1 | 1)
inline LL MAX(LL a, LL b, LL c) {
	return max(a, max(b, c));
}
inline void update(int node) {
	Tr[node].f[0][0] = MAX(Tr[Lnode].f[0][1] + Tr[Rnode].f[0][0], Tr[Lnode].f[0][0] + Tr[Rnode].f[1][0], Tr[Lnode].f[0][0] + Tr[Rnode].f[0][0]);
	Tr[node].f[1][0] = MAX(Tr[Lnode].f[1][1] + Tr[Rnode].f[0][0], Tr[Lnode].f[1][0] + Tr[Rnode].f[1][0], Tr[Lnode].f[1][0] + Tr[Rnode].f[0][0]);
	Tr[node].f[0][1] = MAX(Tr[Lnode].f[0][1] + Tr[Rnode].f[0][1], Tr[Lnode].f[0][0] + Tr[Rnode].f[1][1], Tr[Lnode].f[0][0] + Tr[Rnode].f[0][1]);
	Tr[node].f[1][1] = MAX(Tr[Lnode].f[1][1] + Tr[Rnode].f[0][1], Tr[Lnode].f[1][0] + Tr[Rnode].f[1][1], Tr[Lnode].f[1][0] + Tr[Rnode].f[0][1]);
}
inline void build(int L, int R, int node) {
	Tr[node].l = L, Tr[node].r = R;
	if (L == R) {
		Tr[node].f[1][1] = milk[L];
		return;
	}
	int mid = L + R >> 1;
	build(L, mid, Lnode);
	build(mid + 1, R, Rnode);
	update(node);
}
inline void change(int pos, int val, int node) {
	if (Tr[node].l == pos && Tr[node].r == pos) {
		Tr[node].f[1][1] = val;
		return;
	}
	int mid = Tr[node].l + Tr[node].r >> 1;
	if(pos <= mid) change(pos, val, Lnode);
	else change(pos, val, Rnode);
	update(node);
}
int main() {
	n = read(), d = read();
	for (int i = 1; i <= n; i++) milk[i] = read();
	build(1, n, 1);
	LL sum(0);
	for (int i = 1; i <= d; i++) {
		int index = read(), val = read();
		change(index, val, 1);
		sum += max(Tr[1].f[1][1], MAX(Tr[1].f[1][0], Tr[1].f[0][1], Tr[1].f[0][0]));
	}
	cout << sum << endl;
	return 0;
}