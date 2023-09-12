#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/p3834-mu-ban-ke-chi-jiu-hua-xian-duan-shu-1-zhu-xi-shu-post
//https://www.luogu.com.cn/problem/P3919
constexpr int MAXN= 2e5 + 5;
constexpr int LOG = 64;
using namespace std;
struct Node {
	int cnt, lson, rson;
}Tree[MAXN * LOG];
int arr[MAXN], brr[MAXN], root[MAXN], tot, cnt, n, m;
map<int, int>Map;
inline void discretizaton() {
	sort(brr, brr + n);
	cnt = unique(brr, brr + n) - brr;
	for (int i = 0; i < cnt; i++) Map[brr[i]] = i;
}
inline void build(int &root, int L, int R) {
	root = tot++;
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(Tree[root].lson, L, mid), build(Tree[root].rson, mid + 1, R);
}
inline void modify(int pre, int &cur, int L, int R, int pos) {
	Tree[cur = tot++] = Tree[pre];//拷贝
	if(L == R) {
		Tree[cur].cnt++;
		return;
	}
	int mid = (L + R) >> 1;
	if (pos <= mid) modify(Tree[pre].lson, Tree[cur].lson, L, mid, pos); //右儿子不变 新建左儿子
	else modify(Tree[pre].rson, Tree[cur].rson, mid + 1, R, pos);//左儿子不变 新建右儿子
	Tree[cur].cnt = Tree[Tree[cur].lson].cnt + Tree[Tree[cur].rson].cnt;
}
inline int query(int pre, int cur, int L, int R, int k) {
	if (L == R) return L;
	int mid = L + R >> 1;
	int lcnt = Tree[Tree[cur].lson].cnt - Tree[Tree[pre].lson].cnt;
	if (k <= lcnt) return query(Tree[pre].lson, Tree[cur].lson, L, mid, k);
	else return query(Tree[pre].rson, Tree[cur].rson, mid + 1, R, k - lcnt);
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i], brr[i] = arr[i];
	discretizaton();
	build(root[0], 0, cnt - 1);
	for (int i = 1; i <= n; i++) 
		modify(root[i - 1], root[i], 0, cnt - 1, Map[arr[i - 1]]);
	while (m--) {
		int l, r, k;
		cin >> l >> r >> k;
		int val = query(root[l - 1], root[r], 0, cnt - 1, k);
		cout << brr[val] << endl;
	}
	return 0;
}