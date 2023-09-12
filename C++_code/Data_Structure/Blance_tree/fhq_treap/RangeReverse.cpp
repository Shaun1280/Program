#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3391
const int MAXN = 1e5 + 5;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Treap {
	Treap * lson, *rson;
	int size, priority;
	int key, tag;
}Tree[MAXN << 1], *root, *tmp;
typedef Treap * Node;
#define Lson root->lson
#define Rson root->rson
int n, m, tot, l, r;
inline void newNode(Node &root, int key) {
	root = &Tree[++tot], root->size = 1;
	root->key = key, root->priority = rand();
}
inline void update(Node root) {
	int Lsize = Lson ? Lson->size : 0, Rsize = Rson ? Rson->size : 0;
	root->size = Lsize + Rsize + 1;
}
inline void pushTag(Node root) {
	if (root->tag == 0) return;
	swap(Lson, Rson); //区间反转 交换左右儿子再打上标记即可
	if (Lson) Lson->tag ^= 1; if (Rson) Rson->tag ^= 1;
	root->tag = 0;
}
inline void split(Node root, Node &L, Node &R, int size) {
	if (root == NULL) {
		L = R = NULL;
		return;
	}
	pushTag(root); //分裂前下放标记到左右子树
	int Lsize = Lson ? Lson->size : 0;
	if (Lsize + 1 <= size) L = root, split(Rson, Rson, R, size - Lsize - 1);
	else R = root, split(Lson, L, Lson, size);
	update(root);
}
inline void merge(Node &root, Node L, Node R) {
	if (L == NULL) {root = R; return;}
	if (R == NULL) {root = L; return;}
	if (L->priority < R->priority) pushTag(root = L), merge(Rson, Rson, R);
	else pushTag(root = R), merge(Lson, L, Lson);
	update(root);
}
inline void rev(Node &root, int l, int r) {
	Node L = NULL, mid = NULL, R = NULL;
	split(root, L, R, r), split(L, L, mid, l - 1); //分出[l, r]的部分
	mid->tag ^= 1;
	merge(L, L, mid), merge(root, L, R);
}
inline void print(Node root) { //中序遍历输出
	if (root == NULL) return;
	pushTag(root);
	print(Lson), printf("%d ", root->key), print(Rson);
}
int main() {
	srand(time(0));
	read(n), read(m);
	for (int i = 1; i <= n; i++) 
		newNode(tmp, i), merge(root, root, tmp); //直接merge
	while (m--) read(l), read(r), rev(root, l, r);
	print(root);
	return 0;
}