#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/CF1601B
// CF1601B Frog Traveler
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

template<typename T, int MAXN>
struct Deque {
    int buffer[MAXN * 2];
    int head = MAXN, tail = MAXN - 1;
    bool rev = false;
    bool empty() { return tail < head; }
    int size() { return tail - head + 1; }
    int front() { return rev ? buffer[tail] : buffer[head]; }
    int back() { return rev ? buffer[head] : buffer[tail]; }
    void push_front(int x) { rev ? buffer[++tail] = x : buffer[--head] = x; }
    void push_back(int x) { rev ? buffer[--head] = x : buffer[++tail] = x; }
    void pop_back() { rev ? head++ : tail--; }
    void pop_front() { rev ? tail-- : head++; }
    void reverse() { rev ^= 1; }
};

constexpr int MAXN = 300003, MOD = 1e9 + 7;

int n;
int a[MAXN], b[MAXN];
vector<pair<int, int>> g[MAXN * 6];

#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
struct SegTree { int ls, rs; } tree[MAXN * 6];

void add(int u, int v, int w) { g[u].emplace_back(v, w); }

int tot;
int buildDown(int x, int l, int r) {
    if (l == r) return l;
    x = ++tot;
    int mid = (l + r) >> 1;
    ls(x) = buildDown(ls(x), l, mid);
    rs(x) = buildDown(rs(x), mid + 1, r);
    add(x, ls(x), 0), add(x, rs(x), 0);
    return x;
};

void link(int x, int l, int r, int ql, int qr, int u) { // 
    if (ql <= l && r <= qr) return add(u, x, 1), void();
    int mid = (l + r) >> 1;
    if (ql <= mid) link(ls(x), l, mid, ql, qr, u);
    if (qr > mid) link(rs(x), mid + 1, r, ql, qr, u);
}

int dis[MAXN * 6], pre[MAXN * 6], vis[MAXN * 6];
Deque<int, MAXN * 6> q;
vector<int> nodes;
void bfs(int s = 2 * n) {
    q.push_back(s);
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    dis[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        for (auto& [to, w] : g[cur]) {
            if (dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w;
                pre[to] = cur;
                if (w) q.push_back(to);
                else q.push_front(to);
            }
        }
    }
    if (dis[0] == 0x3f3f3f3f) return cout << -1 << "\n", void();
    cout << dis[0] << "\n";

    int cur = 0;
    while (~pre[cur]) {
        nodes.push_back(cur);
        cur = pre[cur];
    }
    if (nodes.size())
        for (int i = nodes.size() - 1; i >= 0; i--) {
            if (nodes[i] <= n) cout << nodes[i] << " ";
        }
}

void solveOne(int ncase) {
    cin >> n;
    tot = 2 * n;
    int rootdown = buildDown(tot + 1, 0, n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link(rootdown, 0, n, i - a[i], i, i + n);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        add(i, i + n + b[i], 0);
    }
    bfs();
}

int main() {
    boost;
    int testcase = 1;
    // cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}