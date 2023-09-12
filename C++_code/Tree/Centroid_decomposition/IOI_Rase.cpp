#include <bits/stdc++.h>
// P4149 [IOI2011]Race
using namespace std;
// 权值和为 k 的简单路径 最少的边数 点分治
#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n, k, root, tot, cnt, ans = 0x3f3f3f3f;
array<int, MAXN> dp, sz, vis, dis, vecBig;
array<pair<int, int>, MAXN> vec;
array<int, 2000001> minCnt;
vector<pair<int, int>> G[MAXN];

void getRoot(int cur, int fa) {
    sz[cur] = 1, dp[cur] = 0;
    for (auto& e : G[cur]) {
        int to = e.first;
        if (vis[to] || to == fa) continue;
        getRoot(to, cur);
        sz[cur] += sz[to];
        dp[cur] = max(dp[cur], sz[to]);
    }
    dp[cur] = max(dp[cur], tot - sz[cur]);
    if (dp[cur] < dp[root]) root = cur;
}

void getDis(int cur, int fa, int count) {
    vec[cnt++] = {dis[cur], count}; //first dis, second 边数
    for (auto& e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to] || fa == to) continue;
        if (dis[cur] + w <= k) {
            dis[to] = dis[cur] + w;
            getDis(to, cur, count + 1);
        }
    }
}

void calc(int cur) {
    int Cnt = 0;
    for (auto& e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to]) continue;
        cnt = 0, dis[to] = w, getDis(to, cur, 1);
        for (int i = 0; i < cnt; i++) { //不一定有序
            if (vec[i].first > k) continue;
            if (vec[i].first == k) ans = min(ans, vec[i].second); //单条路径
            if (minCnt[k - vec[i].first] == 0x3f3f3f3f) continue;
            ans = min(ans, minCnt[k - vec[i].first] + vec[i].second);
        }
        for (int i = 0; i < cnt; i++) {
            if (vec[i].first > k) break;
            vecBig[Cnt++] = vec[i].first;
            minCnt[vec[i].first] = min(minCnt[vec[i].first], vec[i].second);
            //边权和长度为 i 的最小边数
        }
    }
    for (int i = 0; i < Cnt; i++) minCnt[vecBig[i]] = 0x3f3f3f3f;
    //赋为原来的极大值
}

void dfs(int cur) {
    vis[cur] = true, calc(cur);
    for (auto& e : G[cur]) {
        int to = e.first;
        if (vis[to]) continue;
        root = cur, tot = dp[root] = sz[to];
        getRoot(to, root); //get next centroid
        dfs(root); //start dfs from centroid
    }
}

int main() {
    read(n, k);
    fill(minCnt.begin(), minCnt.end(), 0x3f3f3f3f);
    for (int i = 1, u, v, w; i < n; i++) {
        read(u, v, w);
        u++, v++;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}