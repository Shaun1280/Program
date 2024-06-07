#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF940F
using namespace std;
//CF940F Machine Learning 带修莫队+mex
constexpr int MAXN = 133334;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, m, cntQ, cntR, base;
int col[MAXN], belong[MAXN], cnt[MAXN << 3], ans[MAXN], C[MAXN];

struct Query {
    int l, r, id, tim;
    friend inline bool operator<(const Query& lhs, const Query& rhs) {
        if (belong[lhs.l] != belong[rhs.l]) return lhs.l < rhs.l;
        if (belong[lhs.r] != belong[rhs.r]) return lhs.r < rhs.r;
        return lhs.tim < rhs.tim;
    } //不同块按左端点排序，左端点所在块相同按右端点所在块排序，相同块则按时间排序
} q[MAXN];

struct Change { int pos, col; } chg[MAXN]; //储存修改信息

inline void discrete() {
    vector<int> vec;
    for (int i = 1; i <= n; i++) vec.push_back(col[i]);
    for (int i = 1; i <= cntR; i++) vec.push_back(chg[i].col);
    sort(vec.begin(), vec.end());
    auto edIt = unique(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++) 
        col[i] = lower_bound(vec.begin(), edIt, col[i]) - vec.begin();
    for (int i = 1; i <= cntR; i++)
        chg[i].col = lower_bound(vec.begin(), edIt, chg[i].col) - vec.begin();
}

inline void add(int pos) { --C[cnt[col[pos]]], ++C[++cnt[col[pos]]]; }

inline void del(int pos) { --C[cnt[col[pos]]], ++C[--cnt[col[pos]]]; }

inline void change(int tim, Query& query) { //单点修改
    if (query.l <= chg[tim].pos && chg[tim].pos <= query.r) {
        --C[cnt[col[chg[tim].pos]]], ++C[--cnt[col[chg[tim].pos]]];
        --C[cnt[chg[tim].col]], ++C[++cnt[chg[tim].col]];
    }
    swap(chg[tim].col, col[chg[tim].pos]); //将修改信息交换
}

int main () {
    read(n), read(m), base = pow(n, 0.66);
    for (int i = 1; i <= n; i++) cin >> col[i], belong[i] = i / base;
    while (m--) {
        int opt;
        read(opt);
        if (opt == 1) {
            read(q[++cntQ].l), read(q[cntQ].r);
            q[cntQ].id = cntQ, q[cntQ].tim = cntR;
        } else read(chg[++cntR].pos), read(chg[cntR].col);
    }
    discrete();
    sort(q + 1, q + cntQ + 1);
    int l = 1, r = 0, tim = 0;
    for (int i = 1; i <= cntQ; i++) {
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l); //mo's algorithm 模板
        while (tim < q[i].tim) change(++tim, q[i]); //修改
        while (tim > q[i].tim) change(tim--, q[i]); //修改
        for (ans[q[i].id] = 1; C[ans[q[i].id]] != 0; ans[q[i].id]++);
    }
    for (int i = 1; i <= cntQ; i++) printf("%d\n", ans[i]);
    return 0;
}