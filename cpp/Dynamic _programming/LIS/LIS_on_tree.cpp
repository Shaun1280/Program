#include <bits/stdc++.h>

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

using namespace std;
using LL = long long;

constexpr int MAXN = 2e5 + 5;

struct node {
    node() = default;
    node(int _id, int _val, int _pop): id(_id), preVal(_val), pop(_pop) {}
    int id, preVal, pop;
    //index where val changes, preval, whether vector push_backed
};

int n, val[MAXN], ans[MAXN];
vector<int> G[MAXN], vec;
stack<node> s;

void dfs(int cur, int fa) {
    if (cur == 1) vec.emplace_back(val[cur]), s.push(node(0, 0, true));
    else { // nlogn dp
        if (val[cur] > vec.back()) vec.emplace_back(val[cur]), s.push(node(0, 0, true));
        else {
            int pos = lower_bound(vec.begin(), vec.end(), val[cur]) - vec.begin();
            s.push(node(pos, vec[pos], false));
            vec[pos] = val[cur];
        }
    }
    ans[cur] = vec.size();
    for (auto &to : G[cur]) {
        if (to == fa) continue;
        dfs(to, cur);
    }
    //roll back method
    node tmp = s.top();
    s.pop();
    if (tmp.pop) vec.pop_back();
    else vec[tmp.id] = tmp.preVal;
}

int main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}