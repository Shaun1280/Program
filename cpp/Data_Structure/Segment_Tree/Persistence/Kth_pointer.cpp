#include<bits/stdc++.h>
constexpr int MAXN= 2e5 + 5;
constexpr int LOG = 40;
//https://www.luogu.com.cn/blog/user48611/p3834-mu-ban-ke-chi-jiu-hua-xian-duan-shu-1-zhu-xi-shu-post
//https://www.luogu.com.cn/problem/P3919
using namespace std;
struct Node {
	Node *lson, *rson;
	int cnt;
}Tree[MAXN * LOG], *root[MAXN];
int arr[MAXN], brr[MAXN], tot, cnt, n, m;
map<int, int>Map;
inline void discretizaton() {
	sort(brr, brr + n);
	cnt = unique(brr, brr + n) - brr;
	for (int i = 0; i < cnt; i++) Map[brr[i]] = i;
}
inline Node * newNode(Node * &root/*指针的引用*/) { return root = &Tree[tot++];}
inline void build(Node * root, int L, int R) {
	if (L == R) return;
	int mid = (L + R) >> 1;
	newNode(root->lson), newNode(root->rson); //开辟左右儿子
	build(root->lson, L, mid), build(root->rson, mid + 1, R);
}
inline void modify(Node *pre, Node * cur, int L, int R, int pos) {
	cur->cnt = pre->cnt; //拷贝cnt
	if (L == R) {
		cur->cnt++;
		return;
	}
	int mid = (L + R) >> 1;
	if (pos <= mid)  //连接上个版本的右儿子，开辟新的左儿子
		cur->rson = pre->rson, modify(pre->lson, newNode(cur->lson), L, mid, pos);
	else //连接上个版本的左儿子，开辟新的右儿子
		cur->lson = pre->lson, modify(pre->rson, newNode(cur->rson), mid + 1, R, pos);
	cur->cnt = cur->lson->cnt + cur->rson->cnt; //update
}
inline int query(Node * pre, Node * cur, int L, int R, int k) {
	if (L == R) return L;
	int mid = (L + R) >> 1;
	int lcnt = cur->lson->cnt - pre->lson->cnt; //左儿子的cnt之差
	if (k <= lcnt) return query(pre->lson, cur->lson, L, mid, k);
	else return query(pre->rson, cur->rson, mid + 1, R, k - lcnt);
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i], brr[i] = arr[i];
	discretizaton();
	build(newNode(root[0]), 0, cnt - 1);
	for (int i = 1; i <= n; i++) 
		modify(root[i - 1], newNode(root[i]), 0, cnt - 1, Map[arr[i - 1]]);
	while (m--) {
		int l, r, k;
		cin >> l >> r >> k;
		int val = query(root[l - 1], root[r], 0, cnt - 1, k);
		cout << brr[val] << endl;
	}
	return 0;
}