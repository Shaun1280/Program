#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 6;
const int Inf = 1 << 30;
struct Treap{
    int Lson, Rson;
    int val, dat;
    int cnt, size;
}Tree[MAXN];
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
int tot, root, n;
inline int New(int val){
    Tree[++tot].val = val;
    Tree[tot].dat = rand();
    Tree[tot].cnt = Tree[tot].size = 1; 
    return tot;
}
inline void update(int node){
    Tree[node].size = Tree[Lnode].size + Tree[Rnode].size + Tree[node].cnt;
}
inline void build(){
    New(-Inf), New(Inf);
    root = 1, Tree[root].Rson = 2; 
    update(root);
}
inline int GetRankByVal(int node, int val) {
	if (node == 0) return 0;
	if (val == Tree[node].val) return Tree[Lnode].size + 1;
	if (val < Tree[node].val) return GetRankByVal(Lnode, val);
	return GetRankByVal(Rnode, val) + Tree[Lnode].size + Tree[node].cnt;
}
inline int GetValByRank(int node, int rank) {
	if (node == 0) return Inf;
	if (Tree[Lnode].size >= rank) return GetValByRank(Lnode, rank);
	if (Tree[Lnode].size + Tree[node].cnt >= rank) return Tree[node].val;
	return GetValByRank(Rnode, rank - Tree[Lnode].size - Tree[node].cnt);
}
inline void zig(int &node){
    int p = Lnode;
    Lnode = Tree[p].Rson, Tree[p].Rson = node, node = p; //该节点变为左儿子的右儿子
    update(Rnode), update(node);
}
inline void zag(int &node){
    int p = Rnode;
    Rnode = Tree[p].Lson, Tree[p].Lson = node, node = p; //该节点变为右儿子的左儿子
    update(Lnode), update(node);
}
inline void insert(int &node, int val){
    if(node == 0){
        node = New(val);
        return;
    }
    if(val == Tree[node].val){
        Tree[node].cnt++;
        update(node);  //插入后更新
        return;
    }
    if(val < Tree[node].val){
        insert(Lnode, val);
        if(Tree[node].dat < Tree[Lnode].dat) zig(node); // 不满足堆性质，右旋
    }
    else{
        insert(Rnode, val);
        if(Tree[node].dat < Tree[Rnode].dat) zag(node); // 不满足堆性质，左旋
    }
    update(node);
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
	int nxt = 2; // Tree[2].val == INF
	int node = root;
	while(node){
		if(val == Tree[node].val){
			if(Rnode > 0){
			    node = Rnode;
				while(Lnode > 0) node = Lnode; // 右子树上一直向左走
				nxt = node;
			}
			break;
		}
        //每经过一个结点 尝试更新后继 
		if(Tree[node].val > val && Tree[node].val < Tree[nxt].val) nxt = node;
		node = val < Tree[node].val ? Lnode : Rnode;
	}
	return Tree[nxt].val;
}
inline void Remove(int &node, int val){
	if (node == 0) return;
	if (val == Tree[node].val) { // 检索到了val
		if (Tree[node].cnt > 1) { // 有重复，减少副本数即可
			Tree[node].cnt--;
            update(node);
			return;
		}
		if(Lnode || Rnode){ // 不是叶子节点，向下旋转
			if (Rnode == 0 || Tree[Lnode].dat > Tree[Rnode].dat)
				zig(node), Remove(Rnode, val);
			else
				zag(node), Remove(Lnode, val);
			update(node);
		} else node = 0; // 叶子节点，删除
		return;
	}
	val < Tree[node].val ? Remove(Lnode, val) : Remove(Rnode, val);
	update(node);
}
int main() {
	//srand(time(0));
	build();
	cin >> n;
	while (n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch (opt) {
		case 1:
			insert(root, x);
			break;
		case 2:
			Remove(root, x);
			break;
		case 3:
			printf("%d\n", GetRankByVal(root, x) - 1);
			break;
		case 4:
			printf("%d\n", GetValByRank(root, x + 1));
			break;
		case 5:
			printf("%d\n", GetPre(x));
			break;
		case 6:
			printf("%d\n", GetNext(x));
			break;
		}
	}
}