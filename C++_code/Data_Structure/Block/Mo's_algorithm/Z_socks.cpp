#include<bits/stdc++.h>
//P1494 [国家集训队]小Z的袜子 /【模板】莫队
//https://www.luogu.com.cn/blog/user48611/p1494-guo-jia-ji-xun-dui-xiao-z-di-wa-zi-mu-ban-mu-dui
#define int long long
constexpr int MAXN = 5e4 + 4;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0; 
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, m, Len, l, r, ans;
int c[MAXN], cnt[MAXN];

struct query {
    int l, r, id, block, x/*记录询问分子*/, y/*记录询问分母*/;
}Q[MAXN];

inline bool cmp1 (const query &a, const query &b) {
    return (a.block== b.block) ? a.r < b.r : a.block < b.block;
}

inline bool cmp2 (const query &a, const query &b) { //按照原始顺序排序
    return a.id < b.id;
}

inline int gcd(int x, int y) {
    return !y ? x : gcd(y, x % y);
}

signed main(){
    read(n), read(m), Len = n / sqrt(m * 2.0 / 3);
    for (int i = 1; i <= n; i++) read(c[i]);
    for (int i = 1; i <= m; i++) 
        read(Q[i].l), read(Q[i].r), Q[i].id = i, Q[i].block = Q[i].l / Len;
    sort(Q + 1, Q + m + 1, cmp1);
    l = 1, r = 1, cnt[c[1]]++;
    for (int i = 1; i <= m; i++) {
        while (r < Q[i].r) {
            r++;
            ans -= cnt[c[r]] * (cnt[c[r]] - 1);
            cnt[c[r]]++;
            ans += cnt[c[r]] * (cnt[c[r]] - 1);
        }
        while (r > Q[i].r) {
            ans -= cnt[c[r]] * (cnt[c[r]] - 1);
            cnt[c[r]]--;
            ans += cnt[c[r]] * (cnt[c[r]] - 1);
            r--;
        }
        while (l < Q[i].l) {
            ans -= cnt[c[l]] * (cnt[c[l]] - 1);
            cnt[c[l]]--;
            ans += cnt[c[l]] * (cnt[c[l]] - 1);
            l++;
        }
        while (l > Q[i].l) {
            l--;
            ans -= cnt[c[l]] * (cnt[c[l]] - 1);
            cnt[c[l]]++;
            ans += cnt[c[l]] * (cnt[c[l]] - 1);
        }
        Q[i].x = ans, Q[i].y = (Q[i].r - Q[i].l + 1) * (Q[i].r - Q[i].l);
    }
    sort(Q + 1, Q + m + 1, cmp2);
    for (int i = 1; i <= m; i++)
        if (Q[i].l == Q[i].r) puts("0/1");
        else printf("%lld/%lld\n", Q[i].x / gcd(Q[i].x, Q[i].y), Q[i].y / gcd(Q[i].x, Q[i].y));
	return 0;
}