#include<bits/stdc++.h>
using namespace std;
const int Inf = 0x3f3f3f3f;
const int MAXN = 4e4 + 6;
struct Treap{
	int Lson, Rson;
	int val, dat;
}Tree[MAXN];
int tot, root, n;
map<int, bool>vis;
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
inline int New(int val){
	Tree[++tot].val = val;
	Tree[tot].dat = rand();
	return tot;
}
inline void build(){
	New(-Inf), New(Inf);
	root = 1, Tree[root].Rson = 2;
}
inline void zig(int &node){
	int p = Lnode;
	Lnode = Tree[p].Rson, Tree[p].Rson = node, node = p;
}
inline void zag(int &node){
	int p = Rnode;
	Rnode = Tree[p].Lson, Tree[p].Lson = node, node = p;
}
inline void insert(int &node, int val){
	if(node == 0){
		node = New(val);
		return;
	}
	if(val < Tree[node].val){
		insert(Lnode, val);
		if(Tree[node].dat < Tree[Lnode].dat) zig(node);
	}
	if(val > Tree[node].val){
		insert(Rnode, val);
		if(Tree[node].dat < Tree[Rnode].dat) zag(node);
	}
}
inline int GetPre(int val){
	int pre = 1; // Tree[1].val == -INF
	int node = root;
	while(node){
		if(val == Tree[node].val){
			if(Lnode > 0){
			    node = Lnode;
				while(Rnode > 0) node = Rnode; // 左子树上一直向右走
				pre = node;
			}
			break;
		}
        //每经过一个结点 尝试更新前驱
		if(Tree[node].val < val && Tree[node].val > Tree[pre].val) pre = node;
		node = val < Tree[node].val ? Lnode : Rnode;
	}
	return Tree[pre].val;
}
inline int GetNext(int val){
	int nxt = 2;
	int node = root;
	while(node){
		if(val == Tree[node].val){
			if(Rnode > 0){
				while(Lnode) node = Lnode;
				nxt = node;
			}
			break;
		}
		if(Tree[node].val > val && Tree[nxt].val > Tree[node].val) nxt = node;
		node = val < Tree[node].val ? Lnode : Rnode;
	}
	return Tree[nxt].val;
}
int main(){
	scanf("%d", &n);
	long long ans(0);
	build();
	for(int i = 1, tmp; i <= n; i++){
		scanf("%d", &tmp);
		if(i == 1){
			insert(root, tmp);
			ans += tmp;
			vis[tmp] = true;
			continue;
		}
		if(vis[tmp]) continue;
		int pre = GetPre(tmp), nxt = GetNext(tmp);
		ans += min(abs(tmp - pre), abs(tmp - nxt));
		insert(root, tmp), vis[tmp] = true;
	}
	cout << ans << endl;
	return 0;
}