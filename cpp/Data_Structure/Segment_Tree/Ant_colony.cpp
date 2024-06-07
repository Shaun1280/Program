#include<bits/stdc++.h>

const int MAXN = 1e6 + 6;
// https://www.luogu.com.cn/problem/CF474F   CF474F Ant colony
// range gcd
using namespace std;
#define Lnode (node << 1)
#define Rnode (node << 1 | 1)

struct segTree{
	int l, r;
	int gcd, cnt;
} Tree[MAXN << 2];

int num[MAXN], n, m;

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

segTree operator + (const segTree &Lson, const segTree &Rson){
	segTree tmp;
	tmp.l = Lson.l, tmp.r = Rson.r;
	tmp.gcd = gcd(Lson.gcd, Rson.gcd);
	tmp.cnt = (tmp.gcd == Lson.gcd) * Lson.cnt + (tmp.gcd == Rson.gcd) * Rson.cnt;
	return tmp;
}

void update(int node){
	Tree[node] = Tree[Lnode] + Tree[Rnode];
}

void build(int L, int R, int node){
	Tree[node].l = L, Tree[node].r = R;
	if(L == R){
		Tree[node].cnt = 1, Tree[node].gcd = num[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(L, mid, Lnode);
	build(mid + 1, R, Rnode);
	update(node);
}

segTree query(int L, int R, int node){
	if(Tree[node].l == L && Tree[node].r == R){
		return Tree[node];
	}
	int mid = (Tree[node].l + Tree[node].r) >> 1;
	if(R <= mid) return query(L, R, Lnode);
	else if(L > mid) return query(L, R, Rnode);
	else return query(L, mid, Lnode) + query(mid + 1, R, Rnode);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
	build(1, n, 1);
	scanf("%d", &m);
	while(m--){
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", r - l + 1 - query(l, r, 1).cnt);
	}
	return 0;
}