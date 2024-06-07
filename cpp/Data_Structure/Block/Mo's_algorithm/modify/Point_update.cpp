#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1903
using namespace std;
//P1903 [国家集训队]数颜色 / 维护队列 带修改莫队
constexpr int MAXN = 133334;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, m, cntQ, cntR, base, tot;
int col[MAXN], belong[MAXN], cnt[MAXN << 3], ans[MAXN];

struct Query {
    int l, r, id, tim;
    friend inline bool operator<(const Query& lhs, const Query& rhs) {
        if (belong[lhs.l] != belong[rhs.l]) return lhs.l < rhs.l;
        if (belong[lhs.r] != belong[rhs.r]) return lhs.r < rhs.r;
        return lhs.tim < rhs.tim;
    } //不同块按左端点排序，左端点所在块相同按右端点所在块排序，相同块则按时间排序
} q[MAXN];

struct Change { int pos, col; } chg[MAXN]; //储存修改信息

inline void add(int pos) { if (++cnt[col[pos]] == 1) tot++; }

inline void del(int pos) { if (--cnt[col[pos]] == 0) tot--; }

inline void change(int tim, Query& query) { //单点修改
    if (query.l <= chg[tim].pos && chg[tim].pos <= query.r) {
        if (--cnt[col[chg[tim].pos]] == 0) tot--;
        if (++cnt[chg[tim].col] == 1) tot++;
    }
    swap(chg[tim].col, col[chg[tim].pos]); //将修改信息交换
}

int main () {
    read(n), read(m), base = pow(n, 0.66);
    for (int i = 1; i <= n; i++) cin >> col[i], belong[i] = i / base;
    char opt[2];
    while (m--) {
        scanf("%s", opt);
        if (opt[0] == 'Q') {
            read(q[++cntQ].l), read(q[cntQ].r);
            q[cntQ].id = cntQ, q[cntQ].tim = cntR;
        } else read(chg[++cntR].pos), read(chg[cntR].col);
    }
    sort(q + 1, q + cntQ + 1);
    int l = 1, r = 0, tim = 0;
    for (int i = 1; i <= cntQ; i++) {
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l); //mo's algorithm 模板
        while (tim < q[i].tim) change(++tim, q[i]); //修改
        while (tim > q[i].tim) change(tim--, q[i]); //修改
        ans[q[i].id] = tot;
    }
    for (int i = 1; i <= cntQ; i++) printf("%d\n", ans[i]);
    return 0;
}