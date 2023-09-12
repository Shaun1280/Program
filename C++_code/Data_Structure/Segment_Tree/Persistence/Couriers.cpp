// https://www.luogu.com.cn/problem/P3567
#pragma GCC optimize(2)
#include <bits/stdc++.h>

constexpr int MAXN = 5e5 + 5;
constexpr int LOG = 22;

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}

struct Node {
    int cnt, lson, rson;
} T[MAXN * LOG];
int tot, n, m, arr[MAXN], root[MAXN];

inline int newNode(int &root) { return root = tot++; }

inline void build(int L, int R, int root) {
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(L, mid, newNode(T[root].lson)),
        build(mid + 1, R, newNode(T[root].rson));
}

inline void modify(int pre, int cur, int L, int R, int pos) {
    T[cur] = T[pre];
    if (L == R) {
        T[cur].cnt++;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid)
        modify(T[pre].lson, newNode(T[cur].lson), L, mid, pos);
    else
        modify(T[pre].rson, newNode(T[cur].rson), mid + 1, R, pos);
    T[cur].cnt = T[T[cur].lson].cnt + T[T[cur].rson].cnt;
}

inline int query(int pre, int cur, int L, int R, int times) {
    if (L == R) return L;
    int mid = (L + R) >> 1, ans;
    int cntL = T[T[cur].lson].cnt - T[T[pre].lson].cnt;  //左儿子的cnt之差
    int cntR = T[T[cur].rson].cnt - T[T[pre].rson].cnt;  //右儿子的cnt之差
    if (cntL * 2 > times)
        if (ans = query(T[pre].lson, T[cur].lson, L, mid, times))
            return ans;  //结果不为-1才返回
    if (cntR * 2 > times)
        if (ans = query(T[pre].rson, T[cur].rson, mid + 1, R, times))
            return ans;  //结果不为-1才返回
    return 0;
}

int main() {
    n = read(), m = read();
    build(1, n, newNode(root[0]));
    for (int i = 1; i <= n; i++)
        arr[i] = read(), modify(root[i - 1], newNode(root[i]), 1, n, arr[i]);
    while (m--) {
        int l = read(), r = read();
        printf("%d\n", query(root[l - 1], root[r], 1, n, r - l + 1));
    }
    return 0;
}