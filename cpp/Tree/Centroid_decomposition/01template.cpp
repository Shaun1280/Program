#include <bits/stdc++.h>
// 点分治模板，求长度恰好为 k 的路径条数
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 998244353;

vector<int> g[MAXN];
namespace CentroidDecomposition {
    int D, tot, root;
    long long res;
    int dp[MAXN], sz[MAXN], vis[MAXN], dis[MAXN], cntDis[MAXN];
    int vec[MAXN], vecAll[MAXN], cntVec, cntVecAll;
    void getRoot(int cur, int fa) {  //求树的重心 自上而下
        sz[cur] = 1, dp[cur] = 0;
        for (auto& to : g[cur]) {
            if (to == fa || vis[to]) continue;
            getRoot(to, cur);
            sz[cur] += sz[to];
            dp[cur] = max(dp[cur], sz[to]);
        }
        dp[cur] = max(dp[cur], tot - sz[cur]);
        if (dp[cur] < dp[root]) root = cur;
    }

    void getDis(int cur, int fa) {  // 求出到根 root 的距离
        vec[cntVec++] = dis[cur];
        for (auto& to : g[cur]) {
            if (to == fa || vis[to]) continue;
            dis[to] = dis[cur] + 1;
            getDis(to, cur);
        }
    }

    void calc(int cur, int w, int type) {  // cur 为有根树的根节点(重心)
        cntVec = cntVecAll = 0, dis[cur] = w;
        for (auto& to : g[cur]) {
            if (vis[to]) continue;
            cntVec = 0, dis[to] = dis[cur] + 1;
            getDis(to, cur);
            for (int i = 0; i < cntVec; i++) {
                if (vec[i] == D) res += type;
                else if (vec[i] < D) res += type * cntDis[D - vec[i]];
            }
            for (int i = 0; i < cntVec; i++) cntDis[vec[i]]++, vecAll[cntVecAll++] = vec[i];
        }
        for (int i = 0; i < cntVecAll; i++) cntDis[vecAll[i]] = 0;
    }

    void dfs(int cur) {
        vis[cur] = true, calc(cur, 0, 1);
        for (auto& to : g[cur]) {
            if (vis[to]) continue;
            root = cur, tot = dp[root] = sz[to];  //准备重新选择根节点
            getRoot(to, root), dfs(root);
        }
    }

    long long work(int n, int _D) {
        D = _D, root = 0, tot = dp[root] = n;
        getRoot(1, root), dfs(root);
        return res;
    }
}

int n, k;
signed main() {
    boost;
    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    long long res = CentroidDecomposition::work(n, k);
    return 0;
}