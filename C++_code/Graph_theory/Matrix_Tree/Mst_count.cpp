#include <bits/stdc++.h>
//P4208 [JSOI2008]最小生成树计数 https://www.luogu.com.cn/problem/P4208
using namespace std;
using LL = long long;

constexpr int MAXN = 105;
constexpr int MOD = 31011;

int n, m, ans = 1, fa[MAXN], vis[MAXN], belong[MAXN];
vector<pair<int, pair<int, int>>> vec, eTree;

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) fa[r1] = r2;
}

inline void kruskal(int cnt = 0) {
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(vec.begin(), vec.end());
    for (auto& e : vec) {
        int w = e.first, u = e.second.first, v = e.second.second;
        if (find(u) != find(v)) {
            cnt++;
            Union(u, v);
            eTree.push_back(make_pair(w, make_pair(u, v)));
        }
        if (cnt == n - 1) break;
    }
}

int G[MAXN][MAXN];
inline LL Gauss(int n) {
    LL ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            while (G[j][i]) {
                LL t = G[i][i] / G[j][i];
                for (int k = i; k < n; k++)
                    G[i][k] = ((G[i][k] - t * G[j][k]) % MOD + MOD) % MOD;
                swap(G[i], G[j]);
                ans = -ans;
            }
        ans = ans * G[i][i] % MOD;
    }
    return (ans + MOD) % MOD;
}

inline void add(int u, int v) { G[u][u]++, G[v][v]++, G[u][v]--, G[v][u]--; }

inline int calc(int res = 1) {
    for (int i = 0; i < eTree.size(); i++) {
        if (i && eTree[i - 1].first == eTree[i].first) continue;
        int cnt = 0;
        memset(G, 0, sizeof(G)), memset(vis, 0, sizeof(vis));
        for (int j = 1; j <= n; j++) fa[j] = j;
        for (auto& e : eTree) { //生成树上权值不为eTree[i]的边，求出联通块
            int w = e.first, u = e.second.first, v = e.second.second;
            if (w == eTree[i].first) continue;
            Union(u, v);
        }
        for (int j = 1; j <= n; j++) {//处理连通块数目 方便后续生成树Gauss计数
            if (!vis[find(j)]) vis[find(j)] = ++cnt;
            belong[j] = vis[find(j)];
        }
        for (auto& e : vec) { //所有边，将连通块相连
            int w = e.first, u = e.second.first, v = e.second.second;
            if (w != eTree[i].first) continue;
            add(belong[u], belong[v]); //加边
        }
        res = res * Gauss(cnt) % MOD;
    }
    return res;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        vec.push_back(make_pair(w, make_pair(u, v)));
    }
    kruskal();
    cout << calc() << endl;
    return 0;
}