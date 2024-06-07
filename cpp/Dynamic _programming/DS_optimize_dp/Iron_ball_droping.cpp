#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1442 铁球落地
using namespace std;
//排序 + 线段树预处理 + 线性dp
constexpr int MAXN = 2e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree *lson, *rson;
    int l, r, val, tag;
} * root, tree[MAXN << 1];
int n, h, dp[MAXN][2];
pair<int, pair<int, int>> pf[MAXN];
pair<int, int> to[MAXN];  // first 左端点能到达的平台 second 右端点能到达的平台
vector<int> vec;

inline SegTree* newNode(SegTree*& root) {
    static int tot;
    return root = &tree[tot++];
}

inline void build(SegTree* root, int l, int r) {
    root->l = l, root->r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(newNode(root->lson), l, mid);
    build(newNode(root->rson), mid + 1, r);
}

inline void pushTag(SegTree* root) {
    if (!root->tag) return;
    root->lson->tag = root->rson->tag = root->tag;
    root->lson->val = root->rson->val = root->tag;
    root->tag = 0;
}

inline void modify(SegTree* root, int l, int r, int val) {
    if (l <= root->l && root->r <= r) {
        root->val = val, root->tag = val;
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (l <= mid) modify(root->lson, l, r, val);
    if (r > mid) modify(root->rson, l, r, val);
}

inline int query(SegTree* root, int pos) {
    if (root->l == pos && root->r == pos) return root->val;
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    return pos <= mid ? query(root->lson, pos) : query(root->rson, pos);
}

unordered_map<int, int> mp;
inline void discrete() {
    sort(vec.begin(), vec.end());
    int cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) mp[vec[i]] = i + 1;
}

inline void DP(int st, int x, int y, int res = 2e9) {
    memset(dp, 0x3f, sizeof(dp));
    dp[st][0] = y - pf[st].first + x - pf[st].second.first;
    dp[st][1] = y - pf[st].first + pf[st].second.second - x;
    for (int i = st; i >= 1; i--) {
        if (!to[i].first) res = min(res, dp[i][0] + pf[i].first);
        if (!to[i].second) res = min(res, dp[i][1] + pf[i].first);
        int toL = to[i].first, toR = to[i].second;
        if (toL != 1e9) {
            dp[toL][0] =
                min(dp[toL][0], dp[i][0] + pf[i].first - pf[toL].first +
                                    pf[i].second.first - pf[toL].second.first);
            dp[toL][1] =
                min(dp[toL][1], dp[i][0] + pf[i].first - pf[toL].first -
                                    pf[i].second.first + pf[toL].second.second);
        }
        if (toR != 1e9) {
            dp[toR][0] =
                min(dp[toR][0], dp[i][1] + pf[i].first - pf[toR].first +
                                    pf[i].second.second - pf[toR].second.first);
            dp[toR][1] = min(dp[toR][1],
                             dp[i][1] + pf[i].first - pf[toR].first -
                                 pf[i].second.second + pf[toR].second.second);
        }
    }
    printf("%d\n", res);
}

signed main() {
    read(n), read(h);
    int x, y, st = 0;
    read(x), read(y), vec.push_back(x);
    for (int i = 1; i <= n; i++) {
        read(pf[i].first);          // h
        read(pf[i].second.first);   // l
        read(pf[i].second.second);  // r
        vec.push_back(pf[i].second.first);
        vec.push_back(pf[i].second.second);
    }
    sort(pf + 1, pf + n + 1);
    discrete(), build(newNode(root), 1, 2 * n + 1);
    for (int i = 1; i <= n; i++) {
        int l = query(root, mp[pf[i].second.first]);
        int r = query(root, mp[pf[i].second.second]);
        if (pf[i].first - pf[l].first > h) l = 1e9;
        if (pf[i].first - pf[r].first > h) r = 1e9;
        to[i] = {l, r};
        modify(root, mp[pf[i].second.first], mp[pf[i].second.second], i);
        if (y - pf[i].first <= h && y - pf[i].first >= 0)
            if (query(root, mp[x])) st = i;
    }
    if (st == 0 && y <= h) return printf("%d\n", y), 0;
    DP(st, x, y);
    return 0;
}