#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
//https://www.luogu.com.cn/problem/P1558
//P1558 色板游戏
using namespace std;
struct Node {
	Node * lson, *rson;
	int tag, l, r;
	bitset<32>color;
}Tree[MAXN << 1];
int tot, n, T, Q;
inline Node * newNode(Node * &root) { 
	root = &Tree[++tot];
	return root;
}
inline Node operator + (const Node &Lson, const Node &Rson) {
	Node tmp;
	tmp.l = Lson.l, tmp.r = Rson.r;
	tmp.color = Lson.color | Rson.color;
	return tmp;
}
inline void update(Node *root) {
	Node * lson = root->lson, *rson = root->rson;
	int tag = root->tag;
	*root = *root->lson + *root->rson;
	root->lson = lson, root->rson = rson, root->tag = tag;
}
inline void pushTag(Node *root) {
	if (!root->tag) return;
	int tag = root->tag;
	root->lson->color = root->color;
	root->rson->color = root->color;
	root->lson->tag = root->tag, root->rson->tag = root->tag;
	root->tag = 0;
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) {
		root->color[1] = 1;
		return;
	}
	int mid = (L + R) >> 1;
	build(L, mid, newNode(root->lson)), build(mid + 1, R, newNode(root->rson));
	update(root);
}
inline void change(int L, int R, int tag, Node *root) {
	if (root->l == L && root->r == R) {
		root->color = 1 << tag, root->tag = tag;
		return;
	}
	pushTag(root);
	int mid = (root->l + root->r) >> 1;
	if (R <= mid) change(L, R, tag, root->lson);
	else if(L > mid) change(L, R, tag, root->rson);
	else change(L, mid, tag, root->lson), change(mid + 1, R, tag, root->rson);
	update(root);
}
inline Node query(int L, int R, Node *root) {
	if (root->l == L && root->r == R) 
		return *root;
	int mid = (root->l + root->r) >> 1;
	pushTag(root);
	if (R <= mid) return query(L, R, root->lson);
	else if (L > mid) return query(L, R, root->rson);
	else return query(L, mid, root->lson) + query(mid + 1, R, root->rson);
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> T >> Q;
	build(1, n, Tree);
	while (Q--) {
		char opt; int l, r, color;
		cin >> opt >> l >> r;
		if (l > r) swap(l, r);
		if (opt == 'C') cin >>color, change(l, r, color, Tree);
		if (opt == 'P') cout << query(l, r, Tree).color.count() << endl;
	}
	return 0;
}