#include <bits/stdc++.h>
// https://www.luogu.com.cn/blog/user48611/p2870-usaco07dec-zui-jia-niu-xian-huang-jin-best-cow-line-gold
// P2870 [USACO07DEC]最佳牛线，黄金Best Cow Line, Gold
constexpr int MAXN = 5e5 + 5;
typedef unsigned long long uLL;

constexpr uLL base = 13331;
using namespace std;

int n;
uLL H1[MAXN], H2[MAXN], P[MAXN] = {1};
char s[MAXN], revs[MAXN];
string ans;

inline void Init() {
    for (int i = 1; i <= n; i++) P[i] = P[i - 1] * base;
    for (int i = 1; i <= n; i++) H1[i] = H1[i - 1] * base + s[i] - 'A' + 1;
    for (int i = 1; i <= n; i++) H2[i] = H2[i - 1] * base + revs[i] - 'A' + 1;
}

inline uLL getHash(int l, int r, uLL* H) {
    return H[r] - H[l - 1] * P[r - l + 1];
}

inline bool compare(int l, int r) {
    int len = 1, Lst = l - 1, Rst = n - r;
    while (len) {
        if (Lst + len <= r &&
            getHash(l, Lst + len, H1) == getHash(n - r + 1, Rst + len, H2)) {
            Lst += len, Rst += len, len <<= 1;
        } else
            len >>= 1;
    }
    return s[Lst + 1] < revs[Rst + 1];
}
/*
inline bool compare(int l, int r) {
    int L = 0, R = r - l, len = -1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (getHash(l, l + mid, H1) == getHash(n - r + 1, n - r + 1 + mid, H2))
            len = mid, L = mid + 1;
        else R = mid - 1;
    }
    return s[l + len + 1] < s[r - len - 1];
}
*/
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        getchar(), s[i] = getchar(), revs[n - i + 1] = s[i];
    Init();
    int l = 1, r = n;
    while (l <= r) {
        if (compare(l, r))
            ans += s[l], l++;
        else
            ans += s[r], r--;
    }
    for (int i = 0; i < n; i++) {
        if (i && i % 80 == 0) putchar('\n');
        putchar(ans[i]);
    }
    return 0;
}