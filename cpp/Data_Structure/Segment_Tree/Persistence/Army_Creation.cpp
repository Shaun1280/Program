#include<bits/stdc++.h>
//CF813E Army Creation
//https://www.luogu.com.cn/blog/user48611/cf813e-army-creation
constexpr int MAXN = 1e5 + 5;
constexpr int LOG = 20;
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
int tot, n, m, k, last;
inline Node * newNode(Node * &root) { return root = &Tree[tot++];}
inline void build(int L, int R, Node *root) {
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(L, mid, newNode(root->lson)), build(mid + 1, R, newNode(root->rson));
}
inline void modify(Node *pre, Node *cur, int L, int R, int pos) {
	*cur = *pre;
	if (L == R) {
		cur->cnt++;
		return;
	}
	int mid = (L + R) >> 1;
	if (pos <= mid) modify(pre->lson, newNode(cur->lson), L, mid, pos);
	else modify(pre->rson, newNode(cur->rson), mid + 1, R, pos);
	cur->cnt = cur->lson->cnt + cur->rson->cnt;
}
inline int query(Node * pre, Node * cur, int L, int R, int qL, int qR) {
	if (qL <= L && R <= qR) return cur->cnt - pre->cnt;
	int mid = (L + R ) >> 1, ans = 0;
	if (qL <= mid) ans += query(pre->lson, cur->lson, L, mid, qL, qR);
	if (qR > mid) ans += query(pre->rson, cur->rson, mid + 1, R, qL, qR);
	return ans;
}
vector<int>pos[MAXN];
int main(){
	n = read(), k = read();
	build(0, n, newNode(root[0]));
	for (int i = 1, x; i <= n; i++) {
		x = read(), pos[x].push_back(i);
        int sz = pos[x].size();
        if (sz > k) sz = pos[x][sz - k - 1]; else sz = 0;
        modify(root[i - 1], newNode(root[i]), 0, n, sz);
    }
	m = read();
	while (m--) {
		int l = read(), r = read();
        l = (l + last) % n + 1, r = (r + last) % n + 1;
        if (l > r) swap(l, r);
		printf("%d\n", last = query(root[l - 1], root[r], 0, n, 0, l - 1));
	}
	return 0;
}