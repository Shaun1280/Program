#include <bits/stdc++.h>
//https://codeforces.ml/contest/1453/problem/E
using namespace std;
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int tc, n, ans;
array<int, MAXN> dp; //min dis to the nodes in subtree
vector<int> g[MAXN];

void dfs(int cur, int f) {
    if (g[cur].size() == 1 && cur != 1) return dp[cur] = 1, void();
    vector<int> vec;
    for (auto& to : g[cur]) {
        if (to == f) continue;
        dfs(to, cur);
        vec.push_back(dp[to]);
    }
    sort(vec.begin(), vec.end());
    dp[cur] = vec[0] + 1;
    if (vec.size() > 1) {
        if (cur == 1) ans = max({ans, vec.back(), vec[vec.size() - 2] + 1});
        else ans = max({ans, vec.back() + 1}); //child to child
    }
    ans = max({ans, vec[0]});
}

int main() {
    boost;
    cin >> tc;
    while (tc--) {
        ans = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear(), dp[i] = 0;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].push_back(v), g[v].push_back(u);
        }
        dfs(1, 0);
        cout << ans << "\n";
    }
    return 0;
}
/*
This implies another fact. Let's say the j-th vertex is a child of the i-th
vertex. After visiting the last vertex of a subtree rooted at the j-th vertex,
Badugi has to move a longer distance when it was the last child of the i-th
vertex than when the i-th vertex has another unvisited child. The only important
rule for Badugi is to choose the child that has the shortest 'moving back'
distance as the last child he will visit. This distance can be sent back to its
parent so that the parent can choose between the candidates. Let's say the
minimum among the candidates is mn, and the maximum is mx. It is optimal to use
mn+1 as the 'moving back' distance, and the maximum of the 'child-to-child'
distances will be mx+1.

There is one exception for this strategy – the root. Unlike the others, there is
no need to move any further after visiting all vertices and then getting back to
the root. This means choosing mx as the 'moving back' distance is optimal,
because we don't need to add anything to it. Then we can use the sub-maximum of
the candidates as the maximum of 'child-to-child' distances.
*/