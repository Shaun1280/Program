#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P3605
constexpr int MAXN = 1e5 + 1;
constexpr int LOG = 17;
using namespace std;
template <typename T>
inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Node {
    Node *lson, *rson;
    int cnt;
} Tree[MAXN * LOG * 4], *root[MAXN];
#define Lson root->lson
#define Rson root->rson
vector<int> G[MAXN];
int tot, n, ans[MAXN], val[MAXN], cnt, cpy[MAXN];
unordered_map<int, int> Map;
inline void discretization() {
    sort(cpy + 1, cpy + n + 1);
    cnt = unique(cpy + 1, cpy + n + 1) - cpy - 1;
    for (int i = 1; i <= cnt; i++) Map[cpy[i]] = i;
}
inline Node *newNode(Node *&root) {
    if (root == NULL) root = &Tree[++tot];
    return root;
}
inline void update(Node *root) {
    int Lcnt = Lson == NULL ? 0 : Lson->cnt,
        Rcnt = Rson == NULL ? 0 : Rson->cnt;
    root->cnt = Lcnt + Rcnt;
}
inline void insert(Node *root, int L, int R, int val) {
    if (L == R) {
        root->cnt++;
        return;
    }
    int mid = (L + R) >> 1;
    if (val <= mid)
        insert(newNode(Lson), L, mid, val);
    else
        insert(newNode(Rson), mid + 1, R, val);
    update(root);
}
inline void merge(Node *&root, Node *p, int L, int R) {
    if (root == NULL) {
        root = p;
        return;
    }
    if (p == NULL) return;
    if (L == R) {
        root->cnt += p->cnt;
        return;
    }
    int mid = (L + R) >> 1;
    merge(Lson, p->lson, L, mid);
    merge(Rson, p->rson, mid + 1, R);
    update(root);
}
inline int query(Node *root, int L, int R, int qL, int qR) {
    if (root == NULL) return 0;
    if (qL <= L && R <= qR) return root->cnt;
    int mid = (L + R) >> 1, res = 0;
    if (qL <= mid) res += query(Lson, L, mid, qL, qR);
    if (qR > mid) res += query(Rson, mid + 1, R, qL, qR);
    return res;
}
inline void dfs(int cur) {
    for (auto to : G[cur]) {
        dfs(to);
        merge(root[cur], root[to], 1, cnt);
    }
    ans[cur] = query(root[cur], 1, cnt, Map[val[cur]] + 1, cnt);
}
int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(val[i]), cpy[i] = val[i];
    discretization();
    for (int i = 1; i <= n; i++)
        newNode(root[i]), insert(root[i], 1, cnt, Map[val[i]]);
    for (int i = 2, fa; i <= n; i++) cin >> fa, G[fa].emplace_back(i);
    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}