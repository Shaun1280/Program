#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF85D
constexpr int MAXN = 1e5 + 5;
typedef long long LL;
using namespace std;
int tot, n, cnt;
unordered_map<int, int>Map;
vector<int>vec; //store numbers needed to sort
vector<pair<string, int>>opt;
string s;
inline void discretization() {
    sort(vec.begin(), vec.end());
    cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) Map[vec[i]] = i;
}
struct Node {
	Node * lson, *rson;
	int cnt, l, r; 
    LL sum[5]; //区间内排名mod5余数为i的数的总和
}Tree[MAXN << 1];
#define Lson root->lson
#define Rson root->rson
inline Node * newNode(Node * &root) { 
	return root = &Tree[++tot];
}
inline void update(Node *root) {
	root->cnt = Lson->cnt + Rson->cnt;
    for (int i = 0; i < 5; i++)
        root->sum[i] = Lson->sum[i] + Rson->sum[((i - Lson->cnt) % 5 + 5) % 5];
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(L, mid, newNode(Lson)), build(mid + 1, R, newNode(Rson));
}
inline void modify(int pos, int val, Node *root) {
	if (root->l == pos && root->r == pos) {
		root->cnt += val, root->sum[1] += val * vec[pos];
		return;
	}
	int mid = (root->l + root->r) >> 1;
	if (pos <= mid) modify(pos, val, Lson);
	if (pos > mid) modify(pos, val, Rson);
	update(root);
}
int main(){
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> s;
        if (s == "add") cin >> x, opt.push_back({s, x}), vec.push_back(x);
        else if (s == "del") cin >> x, opt.push_back({s, x});
        else opt.push_back({s, 0});
    }
    discretization(), build(0, cnt, Tree);
    for (auto i : opt) {
        if (i.first == "add") modify(Map[i.second], 1, Tree);
        else if (i.first == "del") modify(Map[i.second], -1, Tree);
        else cout << Tree->sum[3] << endl;
    }
	return 0;
}