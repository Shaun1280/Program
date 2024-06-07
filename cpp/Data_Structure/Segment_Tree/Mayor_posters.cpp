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
struct segTree{
	int Lson, Rson; //左右儿子编号
	int l, r;	//对应值域
	int color;	//颜色标记
};
vector<segTree>Tree;
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
int testCase, root, tot;
inline void build(int &node, int L, int R){
	if(node) return;
	node = ++tot;
	Tree[node].l = L, Tree[node].r = R;
}
inline void pushTag(int node){
	if(!Tree[node].color) return;
	Tree[Lnode].color = Tree[Rnode].color = Tree[node].color;
	Tree[node].color = 0;
}
inline void change(int L, int R, int color, int node){
	if(!node) return;
	if(Tree[node].l == L && Tree[node].r == R){ 
		Tree[node].color = color;
		return;
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	build(Lnode, Tree[node].l, mid), build(Rnode, mid + 1, Tree[node].r); 
		//动态开辟左右儿子 左儿子的左右端点分别为父亲结点的l, mid
	pushTag(node); //下传标记
	if(R <= mid) change(L, R, color, Lnode);
	else if(L > mid) change(L, R, color, Rnode);
	else change(L, mid, color, Lnode), change(mid + 1, R, color, Rnode);
}
set<int>s;
inline void query(int L, int R, int node){
	if(!node) return; //不存在结点 直接return
	if(Tree[node].color){ //叶子节点被染色 存入set 根据set的大小判断显示的海报数
		s.insert(Tree[node].color);
		return;
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	if(R <= mid) query(L, R, Lnode);
	else if(L > mid) query(L, R, Rnode);
	else query(L, mid, Lnode), query(mid + 1, R, Rnode); 
}
int main(){
	testCase = read();
	while(testCase--){
		s.clear();
		root = tot = 0;
		int n = read();
		Tree.clear(), Tree.resize(MAXN * LOG);
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