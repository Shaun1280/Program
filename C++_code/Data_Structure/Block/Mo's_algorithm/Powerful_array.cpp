#include <bits/stdc++.h>
// CF86D Powerful array
// https://www.luogu.com.cn/problem/CF86D
constexpr int MAXN = 1e6 + 6;
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
int n, t, base, a[MAXN], l, r, belong[MAXN];
long long sum, cnt[MAXN], ans[MAXN];
struct query {
    int l, r, id;
    inline friend bool operator<(const query &lhs, const query &rhs) {
        return (belong[lhs.l] == belong[rhs.l])
                   ? ((belong[lhs.l] & 1) ? lhs.r < rhs.r : lhs.r > rhs.r)
                   : lhs.l < rhs.l;
    }
} Q[MAXN];
int main() {
    read(n), read(t), base = pow(n, 0.54);
    for (int i = 1; i <= n; i++) read(a[i]), belong[i] = i / base;
    for (int i = 1; i <= t; i++) read(Q[i].l), read(Q[i].r), Q[i].id = i;
    sort(Q + 1, Q + 1 + t);
    l = 1, r = 0;
    for (int i = 1; i <= t; i++) {
        while (r < Q[i].r) {
            r++;
            sum += (cnt[a[r]] << 1 | 1) * a[r];
            cnt[a[r]]++;
        }
        while (r > Q[i].r) {
            cnt[a[r]]--;
            sum -= (cnt[a[r]] << 1 | 1) * a[r];
            r--;
        }
        while (l < Q[i].l) {
            cnt[a[l]]--;
            sum -= (cnt[a[l]] << 1 | 1) * a[l];
            l++;
        }
        while (l > Q[i].l) {
            l--;
            sum += (cnt[a[l]] << 1 | 1) * a[l];
            cnt[a[l]]++;
        }
        ans[Q[i].id] = sum;
    }
    for (int i = 1; i <= t; i++) printf("%lld\n", ans[i]);
    return 0;
}