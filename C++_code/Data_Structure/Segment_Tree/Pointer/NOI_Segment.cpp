#include<bits/stdc++.h>
//P1712 [NOI2016]区间
constexpr int MAXN = 5e5 + 5;
constexpr int Inf = 2e9;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
int tot, n, m, cnt;
unordered_map<int, int>Map;
vector<int>vec; //store numbers needed to sort
inline void discretization() {
    sort(vec.begin(), vec.end());
    cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) Map[vec[i]] = i;
    vec.clear();
}
struct node {
    int l, r, len;
    inline bool friend operator < (const node &a, const node &b) {
        return a.len < b.len;
    }
}line[MAXN];
struct Node {
	Node * lson, *rson;
	int cnt, tag, l, r;
}Tree[MAXN << 2];
#define Lson root->lson
#define Rson root->rson
inline Node * newNode(Node * &root) { 
	return root = &Tree[++tot];
}
inline void update(Node *root) {
	root->cnt = max(Lson->cnt, Rson->cnt);
}
inline void pushTag(Node *root) {
	if (!root->tag) return;
	Lson->cnt += root->tag, Rson->cnt += root->tag;
	Lson->tag += root->tag, Rson->tag += root->tag;
	root->tag = 0;
}
inline void build(int L, int R, Node *root){
	root->l = L, root->r = R;
	if (L == R) return;
	int mid = (L + R) >> 1;
	build(L, mid, newNode(Lson)), build(mid + 1, R, newNode(Rson));
	update(root);
}
inline void modify(int L, int R, int tag, Node *root) {
	if (L <= root->l && root->r <= R) {
		root->cnt += tag, root->tag += tag;
		return;
	}
	pushTag(root);
	int mid = (root->l + root->r) >> 1;
	if (L <= mid) modify(L, R, tag, Lson);
	if (R > mid) modify(L, R, tag, Rson);
	update(root);
}
int main() {
    read(n), read(m);
    for (int i = 0; i < n; i++) {
        read(line[i].l), read(line[i].r), line[i].len = line[i].r - line[i].l;
        vec.push_back(line[i].l), vec.push_back(line[i].r);
    }
    sort(line, line + n), discretization(), build(0, cnt - 1, Tree);
    int last = 0, ans = Inf;
    for (int i = 0; i < n; i++) {
        modify(Map[line[i].l], Map[line[i].r], 1, Tree);
        while (Tree->cnt == m) {
            modify(Map[line[last].l], Map[line[last].r], -1, Tree);
            ans = min(ans, line[i].len - line[last].len);
            last++;
        }
    }
    cout << (ans == Inf ? -1 : ans) << endl;
	return 0;
}