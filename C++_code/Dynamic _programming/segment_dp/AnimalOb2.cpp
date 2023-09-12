#include<bits/stdc++.h>
constexpr int MAXM = 2e4 + 4;
//dp using data structure
////https://codeforces.com/blog/entry/73934
using namespace std;
struct Node {
	Node * lson, *rson;
	int l, r, mx, tag;
}Tree[MAXM << 1];
int tot, n, m, k, r;
int animal[55][MAXM], sum[55][MAXM], dp[MAXM];
inline void update(Node *root) {
	root->mx = max(root->lson->mx, root->rson->mx);
}
inline void pushTag(Node *root) {
	if(!root->tag) return;
	root->lson->tag += root->tag, root->rson->tag += root->tag;
	root->lson->mx += root->tag, root->rson->mx += root->tag;
	root->tag = 0;
}
inline void build(int L, int R, Node * root){
	root->l = L, root->r = R;
	if (L == R) {
		root->mx = dp[L];
		return;
	}
	int mid = (L + R) >> 1;
	root->lson = &Tree[++tot], root->rson = &Tree[++tot];
	build(L, mid, root->lson), build(mid + 1, R, root->rson);
	update(root);
}
inline void change(int L, int R, int tag, Node *root) {
	if (root == nullptr) return;
	if (root->l == L && root->r == R) {
		root->mx += tag, root->tag += tag;	
		return;
	}
	pushTag(root);
	int mid = (root->l + root->r) >> 1;
	if (R <= mid) change(L, R, tag, root->lson);
	else if(L > mid) change(L, R, tag, root->rson);
	else change(L, mid, tag, root->lson), change(mid + 1, R, tag, root->rson);
	update(root);
}
inline int getSum(int t, int l, int r) {
	return sum[t][r] - sum[t][l - 1];
}
int main(){
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m >> k, r = m - k + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> animal[i][j];
			sum[i][j] = sum[i][j - 1] + animal[i][j];
		}
	}
	for (int i = 1; i <= r; i++) dp[i] = getSum(1, i, i + k - 1) + getSum(2, i, i + k - 1);
	for (int i = 2; i <= n; i++) {
		memset(Tree, 0, sizeof(Tree)), tot = 0;
		build(1, m + 1, Tree);
		for (int j = 1; j <= k; j++) change(1, j, -animal[i][j], Tree);
		for (int j = 1; j <= r; j++) {
			dp[j] = Tree->mx + getSum(i, j, j + k - 1) + getSum(i + 1, j , j + k - 1);
			change(max(1, j - k + 1), j, animal[i][j], Tree); //j is not in range, add it back
			change(j + 1, j + k, -animal[i][j + k], Tree); //j + k is in range, subtract it
		}
	}
	cout << *(max_element(dp + 1, dp + r + 1)) << endl;
	return 0;
}