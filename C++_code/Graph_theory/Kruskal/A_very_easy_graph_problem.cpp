#include <bits/stdc++.h>
//http://acm.hdu.edu.cn/showproblem.php?pid=6832 
using namespace std;
using LL = long long;
//A Very Easy Graph Problem
constexpr int MAXN = 1e5 + 5;
constexpr LL INF = 1e16;
constexpr LL MOD = 1e9 + 7;

LL t, n, m, a[MAXN], dis[MAXN][2], cnt[MAXN][2], fa[MAXN], d[MAXN], ans;
vector<pair<LL, pair<LL, LL>>> e;
vector<pair<LL, LL>> G[MAXN];

inline LL qpow(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) fa[r1] = r2;
}

inline void kruskal() { //最小生成树建图
    sort(e.begin(), e.end());
    int cnt = 0;
    for (auto& eg : e) {
        LL i = qpow(2, eg.first), u = eg.second.first, v = eg.second.second;
        if (find(u) != find(v)) {
            Union(u, v);
            cnt++;
            G[u].emplace_back(v, i);
            G[v].emplace_back(u, i);
        }
        if (cnt == n - 1) break;
    }
}

void dfs(int cur, int fa, LL len = 0) { //树上dp
    (d[cur] = d[fa] + len) %= MOD; //到root的距离
    dis[cur][a[cur]] = d[cur]; //对应编号到根的距离总和
    cnt[cur][a[cur]] = 1; //对应编号计数1次

    LL sumCnt0 = 0, sumCnt1 = 0;
    for (auto& e : G[cur]) {
        LL to = e.first, w = e.second;
        if (to == fa) continue;
        dfs(to, cur, w);
        (dis[cur][0] += dis[to][0]) %= MOD;
        (dis[cur][1] += dis[to][1]) %= MOD;
        cnt[cur][0] += cnt[to][0];
        cnt[cur][1] += cnt[to][1];
        sumCnt0 += cnt[to][0]; //子树0计数和
        sumCnt1 += cnt[to][1]; //子树1计数和
    }
    if (!a[cur]) sumCnt0++; //加上根节点计数
    else sumCnt1++;

    for (auto& e : G[cur]) {
        LL to = e.first, w = e.second;
        if (to == fa) continue;
        LL tmp0 = (dis[to][0] - d[cur] * cnt[to][0] % MOD) % MOD;
        tmp0 = (tmp0 + MOD) % MOD; //0的贡献
        LL tmp1 = (dis[to][1] - d[cur] * cnt[to][1] % MOD) % MOD;
        tmp1 = (tmp1 + MOD) % MOD; //1的贡献
        ans = (ans + tmp0 * (sumCnt1 - cnt[to][1]) % MOD) % MOD;
        ans = (ans + tmp1 * (sumCnt0 - cnt[to][0]) % MOD) % MOD;
    }
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        e.clear(); //清空
        ans = 0;
        for (int i = 0; i < MAXN; i++) G[i].clear(); //清空
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i], fa[i] = i; //并查集初始化
        memset(dis, 0, sizeof(dis)), memset(cnt, 0, sizeof(cnt));
        memset(d, 0, sizeof(d)); //数组清零
        for (LL i = 1, u, v; i <= m; i++) {
            cin >> u >> v;  // first
            e.push_back(make_pair(i, make_pair(u, v)));
            //存边 之后按第一关键字排序
        }
        kruskal(); //最小生成树建图
        dfs(1, 0); //dp
        cout << ans << endl;
    }
    return 0;
}