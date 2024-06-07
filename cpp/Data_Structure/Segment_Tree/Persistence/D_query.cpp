#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/sp3267-dquery-d-query
//SP3267 DQUERY - D-query
constexpr int MAXN = 3e4 + 4;
constexpr int MAXA = 1e6 + 6;
constexpr int LOG = 23;
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
int tot, n, m, cnt, arr[MAXN], pre[MAXA], last[MAXN];
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
inline int query(Node * pre, Node * cur, int L, int R, int qL, int qR) {
	if (qL <= L && R <= qR) return cur->cnt - pre->cnt;
	int mid = (L + R ) >> 1, ans = 0;
	if (qL <= mid) ans += query(pre->lson, cur->lson, L, mid, qL, qR);
	if (qR > mid) ans += query(pre->rson, cur->rson, mid + 1, R, qL, qR);
	return ans;
}
// inline int query2(Node * pre, Node * cur, int L, int R, int qL, int qR) {
// 	if (qL == L && R == qR) return cur->cnt - pre->cnt;
// 	int mid = (L + R ) >> 1;
// 	if (qR <= mid) return query2(pre->lson, cur->lson, L, mid, qL, qR);
// 	else if (qL > mid) return query2(pre->rson, cur->rson, mid + 1, R, qL, qR);
// 	else return query2(pre->lson, cur->lson, L, mid, qL, mid) + query2(pre->rson, cur->rson, mid + 1, R, mid + 1, qR);
// }
int main(){
	n = read();
	build(0, n, newNode(root[0]));
	for (int i = 1; i <= n; i++) {
		arr[i] = read(), last[i] = pre[arr[i]], pre[arr[i]] = i;
		modify(root[i - 1], newNode(root[i]), 0, n, last[i]);
	}
	m = read();
	while (m--) {
		int l = read(), r = read();
		printf("%d\n", query(root[l - 1], root[r], 0, n, 0, l - 1));
	}
	return 0;
}