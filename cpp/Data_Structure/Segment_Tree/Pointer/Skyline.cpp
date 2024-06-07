//UVA1232 SKYLINE
//https://www.luogu.com.cn/problem/UVA1232
#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Node {
	Node * lson, *rson;
	int max, min, l, r, tag; 
}Tree[MAXN << 1];
int tot, testCase, n, sum;
#define Lson root->lson
#define Rson root->rson
inline Node * newNode(Node * &root) { 
	return root = &Tree[++tot];
}
inline void update(Node *root) {
	root->max = max(Lson->max, Rson->max);
    root->min = min(Lson->min, Rson->min);
}
inline void pushtag(Node *root) {
    if (!root->tag) return;
    Lson->tag = Rson->tag = root->tag;
    Lson->max = Rson->max = Lson->min = Rson->min = root->tag;
    root->tag = 0;
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(L, mid, newNode(Lson)), build(mid + 1, R, newNode(Rson));
}
inline void modify(int L, int R, int val, Node *root) {
    if (root->min > val) return;
	if (L == root->l && root->r == R) {
		if (root->max <= val) {
            root->max = root->min = root->tag = val;
            sum += R - L + 1;
            return;
        }
        if (L == R) return;
	}
    pushtag(root);
	int mid = (root->l + root->r) >> 1;
	if (R <= mid) modify(L, R, val, Lson);
	else if (L > mid) modify(L, R, val, Rson);
    else modify(L, mid, val, Lson), modify(mid + 1, R, val, Rson);
	update(root);
}
int main(){
    read(testCase);
    while (testCase--) {
        read(n);
        memset(Tree, 0, sizeof(Tree)), tot = 0, sum = 0;
        build(1, MAXN - 5, Tree);
        for (int i = 1; i <= n; i++) {
            int l, r, h; 
            read(l), read(r), read(h);
            modify(l, r - 1, h, Tree);
        }
        printf("%d\n", sum);
    }
	return 0;
}