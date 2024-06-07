#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
//CF558E A Simple Task
//https://www.luogu.com.cn/problem/CF558E
//https://codeforces.com/blog/entry/19212
using namespace std;
struct Node {
	Node * lson, *rson;
	int cnt, tag, l, r;
}Tree[26 * MAXN << 1], *root[26];
int tot, ch, n, q;;
string s;
inline Node * newNode(Node * &root) { 
	root = &Tree[tot++], root->tag = -1;
	return root;
}
inline void update(Node *root) {
	root->cnt = root->lson->cnt + root->rson->cnt;
}
inline void pushTag(Node *root) {
	if (root->tag == -1) return;
	int l = root->l, r = root->r, mid = (l + r) >> 1;
	root->lson->cnt = root->tag * (mid - l + 1);
	root->rson->cnt = root->tag * (r - mid);
	root->lson->tag = root->tag, root->rson->tag = root->tag;
	root->tag = -1;
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) {
		if (ch == s[L] - 'a') root->cnt = 1;
		return;
	}
	int mid = (L + R) >> 1;
	build(L, mid, newNode(root->lson)), build(mid + 1, R, newNode(root->rson));
	update(root);
}
inline void change(int L, int R, int tag, Node *root) {
	if (root->l == L && root->r == R) {
		root->cnt = tag * (R - L + 1), root->tag = tag;
		return;
	}
	pushTag(root);
	int mid = (root->l + root->r) >> 1;
	if (R <= mid) change(L, R, tag, root->lson);
	else if(L > mid) change(L, R, tag, root->rson);
	else change(L, mid, tag, root->lson), change(mid + 1, R, tag, root->rson);
	update(root);
}
inline int query(int L, int R, Node *root) {
	if (root->l == L && root->r == R) 
		return root->cnt;
	int mid = (root->l + root->r) >> 1;
	pushTag(root);
	if (R <= mid) return query(L, R, root->lson);
	else if (L > mid) return query(L, R, root->rson);
	else return query(L, mid, root->lson) + query(mid + 1, R, root->rson);
}
inline void printTree(Node *root) {
	int l = root->l, r = root->r;
	if (root->cnt == r - l + 1) {
		for (int i = l; i <= r; i++) s[i] = ch + 'a';
		return;
	}
	if (l == r) return;
	pushTag(root);
	if (root->lson->cnt) printTree(root->lson);
	if (root->rson->cnt) printTree(root->rson);
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> q >> s;
	for (ch = 0; ch < 26; ch++) build(0, n - 1, newNode(root[ch]));
	while (q--) {
		int l, r, k, st, len;
		cin >> l >> r >> k, l--, r--, st = l;
		if (k == 1) { //ascending order
			for (ch = 0; ch < 26; ch++) {
				if (!(len = query(l, r, root[ch]))) continue;
				change(l, r, 0, root[ch]), change(st, st + len - 1, 1, root[ch]);
				st += len;
			}
		} else {
			for (ch = 25; ch >= 0; ch--) {
				if (!(len = query(l, r, root[ch]))) continue;
				change(l, r, 0, root[ch]), change(st, st + len - 1, 1, root[ch]);
				st += len;
			}
		}
	}
	for (ch = 0; ch < 26; ch++) printTree(root[ch]);
	cout << s << endl;
	return 0;
}