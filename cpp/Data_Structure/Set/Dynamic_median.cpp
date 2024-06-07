#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc218/submissions/25804040
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n;
int dp[MAXN], a[MAXN];
vector<int> g[MAXN];

multiset<int> s1, s2;
void adjust() {
    if (s1.size() + 1 < s2.size()) {
        auto it = s2.begin();
        s2.erase(it);
        s1.insert(*it);
    } else if (s2.size() + 1 < s1.size()) {
        auto it = s1.end();
        --it;
        s1.erase(it);
        s2.insert(*it);
    }
}

void insert(int x) {
    if (!s2.size()) s2.insert(x);
    else {
        if (x > *s2.begin()) s2.insert(x);
        else s1.insert(x);
    }
    adjust();
}

void remove(int x) {
    if (s1.count(x)) s1.erase(s1.find(x));
    else if (s2.count(x)) s2.erase(s2.find(x));
    adjust();
}

int median() {
    adjust();
    auto it1 = s1.end();
    auto it2 = s2.begin();
    if (s1.size() == s2.size()) return ((*--it1) + (*it2)) >> 1;
    else if (s1.size() > s2.size()) return *--it1;
    else return *it2;
}

void DP(int cur, int f, bool isMax) {
    int mn = 2e9, mx = 0;

    insert(a[cur]);

    for (auto& to : g[cur]) {
        if (to == f) continue;
        DP(to, cur, isMax ^ 1);
        mn = min(mn, dp[to]), mx = max(mx, dp[to]);
    }
    if (mx == 0) dp[cur] = median();
    else if (isMax) dp[cur] = mx;
    else dp[cur] = mn;

    remove(a[cur]);
}

int main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DP(1, 0, true);
    cout << dp[1] << "\n";
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */