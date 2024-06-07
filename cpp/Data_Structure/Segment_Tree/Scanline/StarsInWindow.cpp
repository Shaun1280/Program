#include<bits/stdc++.h>
constexpr int MAXN = 2e4 + 4;
//P1502 窗口的星星
using namespace std;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct Scanline {
	int y, l, r, tag;
	Scanline(){}
	Scanline(int _y, int _l ,int _r, int _tag): y(_y), l(_l), r(_r), tag(_tag){}
	inline friend bool operator < (const Scanline &a, const Scanline &b) {
		if (a.y == b.y) return a.tag > b.tag;
		return a.y < b.y;
	}
};
vector<Scanline>vec;
struct Node {
	Node * lson, *rson;
	int l, r;
	long long max, tag;
}Tree[MAXN << 2];
long long mx, tot, cnt;
vector<int>num;
map<int, int>Map;
inline void discretizaton() {
	sort(num.begin(), num.end());
	cnt = unique(num.begin(), num.end()) - num.begin();
	for (int i = 0; i < cnt; i++) Map[num[i]] = i;
}
inline void update(Node *root) {
	root->max = max(root->lson->max, root->rson->max);
}
inline void pushTag(Node *root) {
	if (root->tag == 0) return;
	root->lson->max += root->tag, root->rson->max += root->tag;
	root->lson->tag += root->tag, root->rson->tag += root->tag;
	root->tag = 0;
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) return;
	int mid = (L + R) >> 1;
	root->lson = &Tree[++tot], root->rson = &Tree[++tot];
	build(L, mid, root->lson), build(mid + 1, R, root->rson);
}
inline void change(int L, int R, int tag, Node *root) {
	if (root->l == L && root->r == R) {
		root->max += tag, root->tag += tag;
		return;
	}
	pushTag(root);
	int mid = (root->l + root->r) >> 1;
	if (R <= mid) change(L, R, tag, root->lson);
	else if(L > mid) change(L, R, tag, root->rson);
	else change(L, mid, tag, root->lson), change(mid + 1, R, tag, root->rson);
	update(root);
}
int main(){
	int testCase = read();
	while (testCase--) {
		int n = read(), w = read(), h = read();
		vec.clear(), num.clear(), Map.clear();
		memset(Tree, 0, sizeof(Tree));
		cnt = 0, tot = 0, mx = 0;
		for (int i = 0, x, y, l; i < n; i++) {
			x = read(), y = read(), l = read();
			vec.push_back(Scanline(y, x, x + w - 1, l));
			vec.push_back(Scanline(y + h - 1, x, x + w - 1, -l));
			num.push_back(x), num.push_back(x + w - 1);
		}
		discretizaton();
		build(0, cnt - 1, Tree);
		sort (vec.begin(), vec.end());
		for (int i = 0; i < vec.size(); i++) {
			int l = vec[i].l, r = vec[i].r, tag = vec[i].tag;
			change(Map[l], Map[r], tag, Tree);
			mx = max(mx, Tree->max);
		}
		cout << mx << endl;
	}
	return 0;
}