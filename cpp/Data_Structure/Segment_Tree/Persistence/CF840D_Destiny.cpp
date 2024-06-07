//https://www.luogu.com.cn/problem/CF840D
#pragma GCC optimize(2)
#include<bits/stdc++.h>
constexpr int MAXN = 3e5 + 5;
constexpr int LOG = 32;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch -48, ch = getchar();
    return x * f;
}
struct Node {
	Node * lson, *rson;
	int cnt;
}Tree[MAXN * LOG], *root[MAXN];
int tot, n, m, k, arr[MAXN];
inline Node * newNode(Node * &root) { return root = &Tree[tot++];}
inline void build(int L, int R, Node *root) {
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(L, mid, newNode(root->lson)), build(mid + 1, R, newNode(root->rson));
}
inline void modify(Node *pre, Node *cur, int L, int R, int pos) {
	cur->cnt = pre->cnt;
	if (L == R) {
		cur->cnt++;
		return;
	}
	int mid = (L + R) >> 1;
	if (pos <= mid) cur->rson = pre->rson, modify(pre->lson, newNode(cur->lson), L, mid, pos);
	else cur->lson = pre->lson, modify(pre->rson, newNode(cur->rson), mid + 1, R, pos);
	cur->cnt = cur->lson->cnt + cur->rson->cnt;
}
inline int query(Node * pre, Node * cur, int L, int R, int times) {
	if (L == R) return L;
	int mid = (L + R ) >> 1, ans;
	int cntL = cur->lson->cnt - pre->lson->cnt; //左儿子的cnt之差
	int cntR = cur->rson->cnt - pre->rson->cnt; //右儿子的cnt之差
	if (cntL * k > times) 
		if (~(ans = query(pre->lson, cur->lson, L, mid, times))) return ans; //结果不为-1才返回
	if (cntR * k> times) 
		if (~(ans = query(pre->rson, cur->rson, mid + 1, R, times))) return ans; //结果不为-1才返回
	return -1;
}
int main(){
	n = read(), m = read();
	build(1, n, newNode(root[0]));
	for (int i = 1; i <= n; i++)
		arr[i] = read(), modify(root[i - 1], newNode(root[i]), 1, n, arr[i]);
	while (m--) {
		int l = read(), r = read(); k = read();
		printf("%d\n", query(root[l - 1], root[r], 1, n, (r - l + 1)));
	}
	return 0;
}