#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
constexpr int Inf = 0x3f3f3f3f;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Treap {
	Treap *lson, *rson;
	int key, priority;
	int cnt, size;
}Tree[MAXN << 1], *rt;
#define Lson root->lson
#define Rson root->rson
int tot, Q, type, x;
inline void newNode(Treap *&root, int key) {
	root = &Tree[tot++];
	root->cnt = root->size = 1;
	root->key = key, root->priority = rand();
}
inline void update(Treap *root) {
	if (root == NULL) return; //空指针直接return
	int Lsize = (Lson == NULL) ? 0 : Lson->size, Rsize = (Rson == NULL) ? 0 : Rson->size;
	root->size = Lsize + Rsize + root->cnt;
}
inline void Lrotate(Treap *&root) { //左旋
	Treap *R = Rson;
	Rson = R->lson, R->lson = root, root = R;
	update(root->lson), update(root);
}
inline void Rrotate(Treap *&root) { //右旋
	Treap *L = Lson;
	Lson = L->rson, L->rson = root, root = L;
	update(root->rson), update(root);
}
inline int getPre(Treap *root, int key, int pre) {
	if (root == NULL) return pre;
	if (key <= root->key) return getPre(Lson, key, pre);
	return getPre(Rson, key, max(pre, root->key));
}
inline int getNext(Treap *root, int key, int next) {
	if (root == NULL) return next;
	if (key >= root->key) return getNext(Rson, key, next);
	return getNext(Lson, key, min(next, root->key));
}
inline int getRank(Treap *root, int key) {
	if (root == NULL) return 0;
	int Lsize = Lson == NULL ? 0 : Lson->size; //左儿子有多少数
	if (key == root->key) return Lsize + 1; 
	if (key < root->key) return getRank(Lson, key);
	return getRank(Rson, key) + Lsize + root->cnt;
}
inline int getVal(Treap *root, int rank) {
	if (root == NULL) return Inf; 
	int Lsize = Lson == NULL ? 0 : Lson->size; //左儿子有多少数
	if (Lsize >= rank) return getVal(Lson, rank); 
	if (Lsize + root->cnt >= rank) return root->key;
	return getVal(Rson, rank - Lsize - root->cnt);
}
inline void insert(Treap *&root, int key) {
	if (root == NULL) { //不存在该key 新建节点
		newNode(root, key);
		return;
	}
	if (key == root->key) root->cnt++, update(root); //已存在key cnt++, update
	else if (key < root->key) { //搜索左儿子
		insert(Lson, key);
		if (root->priority < Lson->priority) Rrotate(root);
	} else {
		insert(Rson, key); //搜索右儿子
		if (root->priority < Rson->priority) Lrotate(root);
	}
	update(root);
}
inline void remove(Treap *&root, int key) {
	if (root == NULL) return;
	if (key == root->key) {
		if (root->cnt > 1) root->cnt--; //副本减少1
		else if (root->rson == NULL) root = root->lson; //右儿子为空 该点地址变为左儿子的
		else if (root->lson == NULL) root = root->rson; //左儿子为空 该点地址变为右儿子的
		else { //根据priority将该节点旋转至根 注意root可能旋为NULL
			if (Lson->priority > Rson->priority) Rrotate(root), remove(Rson, key);
			else Lrotate(root), remove(Lson, key);
		}
	} else key < root->key ? remove(Lson, key) : remove(Rson, key); //查找左右儿子
	update(root);
}
int main(){
	srand(time(0));
	read(Q);
    while (Q--) {
        read(type), read(x);
        switch (type) {
            case 1:
                insert(rt, x);
                break;
            case 2:
                remove(rt, x);
                break;
            case 3:
                printf("%d\n", getRank(rt, x));
                break;
            case 4:
                printf("%d\n", getVal(rt, x));
                break;
            case 5:
                printf("%d\n", getPre(rt, x, -Inf));
                break;
            case 6:
                printf("%d\n", getNext(rt, x, Inf));
                break;
        }
    }
	return 0;
}