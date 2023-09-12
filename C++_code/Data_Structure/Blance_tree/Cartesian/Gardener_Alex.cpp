#include <bits/stdc++.h>
//https://codeforces.ml/contest/1220
using namespace std;
//笛卡尔树+二分+ST表O(1)求区间最小值
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7, LOG = 18;

int n, cycle;
array<int, MAXN * 2> a;
pair<int, int> ST[MAXN][LOG];

int query(int l, int r) {
    int lg = log2(r - l + 1);
    return min(ST[l][lg], ST[r - (1 << lg) + 1][lg]).second;
}

int get(int l, int r) {
    if (r < l) return 0;
    if (r - l == 0) return 1;
    int mid = query(l, r);
    return max(get(l, mid - 1), get(mid + 1, r)) + 1;
}

int main() {
    boost;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 1) cycle = i; //put 1 at the begining
    }
    for (int i = 0; i < n; i++) a[i + n] = a[i];
    for (int i = 0; i < n; i++) a[i] = a[n + ((i + cycle) % n)];
    for (int i = 0; i < n; i++) ST[i][0] = {a[i], i};
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
    
    int l = 1, r = n - 1, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (get(1, mid) > get(mid + 1, n - 1)) r = mid - 1;
        else l = mid + 1, ans = mid;
    }
    cout << max(get(1, ans - 1), get(ans + 1, n - 1)) + 1 << " " << (cycle + ans + 1) % n << "\n";
    return 0;
}