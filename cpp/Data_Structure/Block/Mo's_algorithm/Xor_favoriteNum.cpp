#include <bits/stdc++.h>
// https://www.luogu.com.cn/blog/user48611/cf617e-xor-and-favorite-number
// https://www.luogu.com.cn/problem/CF617E
constexpr int MAXN = 1e5 + 5;

using namespace std;

int n, m, k, base, block[MAXN], a[MAXN];
long long Cnt, ans[MAXN], cnt[MAXN << 4];

template <typename T>
inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct query {
    int l, r, id;
    inline friend bool operator<(const query &a, const query &b) {
        return (block[a.l] == block[b.l])
                   ? ((block[a.l] & 1) ? a.r < b.r : a.r > b.r)
                   : a.l < b.l;
    }
} Q[MAXN];

inline void add(int x) {
    Cnt += cnt[x ^ k];  // a[i] ^ a[j - 1] = k ==> how many a[j - 1] = a[i] ^ k
    cnt[x]++;
}

inline void del(int x) {
    cnt[x]--;
    Cnt -= cnt[x ^ k];
}

int main() {
    read(n), read(m), read(k), base = pow(n, 0.54);
    for (int i = 1; i <= n; i++)
        read(a[i]), a[i] ^= a[i - 1], block[i] = i / base;
    for (int i = 1; i <= m; i++)
        read(Q[i].l), Q[i].l--, read(Q[i].r), Q[i].id = i;
    sort(Q + 1, Q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (r < Q[i].r) add(a[++r]);
        while (r > Q[i].r) del(a[r--]);
        while (l < Q[i].l) del(a[l++]);
        while (l > Q[i].l) add(a[--l]);
        ans[Q[i].id] = Cnt;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}