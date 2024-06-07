#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 4;
//https://www.luogu.com.cn/blog/user48611/uva10587-mayors-posters
const int LOG = 40;
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
struct Node{
	Node * lson, *rson; //左右儿子
	int l, r;	//对应值域
	int color;	//颜色标记
}Tree[MAXN * LOG], *root;
int testCase, tot;
inline void build(Node * &root/*指针的引用*/, int L, int R){
	if(root != nullptr) root = &Tree[tot++], root->l = L, root->r = R;
}
inline void pushTag(Node * root){
	if(!root->color) return;
	root->lson->color = root->rson->color = root->color;
	root->color = 0;
}
inline void change(int L, int R, int color, Node * root){
	if(root == nullptr) return;
	if(root->l == L && root->r == R){ 
		root->color = color;
		return;
	}
	int mid = (root->l + root->r) >> 1;
	build(root->lson, root->l, mid), build(root->rson, mid + 1, root->r); 
		//动态开辟左右儿子 左儿子的左右端点分别为父亲结点的l, mid
	pushTag(root); //下传标记
	if(R <= mid) change(L, R, color, root->lson);
	else if(L > mid) change(L, R, color, root->rson);
	else change(L, mid, color, root->lson), change(mid + 1, R, color, root->rson);
}
set<int>s;
inline void query(int L, int R, Node * root){
	if(root == nullptr) return; //不存在结点 直接return
	if(root->color){ //叶子节点被染色 存入set 根据set的大小判断显示的海报数
		s.insert(root->color);
		return;
	}
	int mid = (root->l + root->r) >> 1;
	if(R <= mid) query(L, R, root->lson);
	else if(L > mid) query(L, R, root->rson);
	else query(L, mid, root->lson), query(mid + 1, R, root->rson); 
}
int main(){
	testCase = read();
	while(testCase--){
		s.clear(), tot = 0, root = nullptr;
		int n = read();
		memset(Tree, 0, sizeof(Tree));
		build(root, 1, 1e7);
		for(int i = 1; i <= n; i++){
			int l = read(), r = read();
			change(l, r, i, root);
		}
		query(1, 1e7, root);
		cout << s.size() << endl;
	}
	return 0;
}