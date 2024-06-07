#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc215/tasks/abc215_f
// dist(i, j) = min(|xi - xj|, |yi - yj|)
// 二分 + 队列滑动窗口
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n;
pair<int, int> p[MAXN];

bool check(int mid) {
    queue<int> q;
    int mn = 1e9, mx = 0;
    for (int i = 1; i <= n; i++) {
        while (!q.empty()) {
            if (p[i].first - p[q.front()].first < mid) break;
            mn = min(mn, p[q.front()].second), mx = max(mx, p[q.front()].second);
            q.pop(); // [0, x - mid]
        }
        if (mx - p[i].second >= mid || p[i].second - mn >= mid) return true;
        q.push(i);
    }
    return false;
}

int main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
    sort(p + 1, p + n + 1);
    int l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */