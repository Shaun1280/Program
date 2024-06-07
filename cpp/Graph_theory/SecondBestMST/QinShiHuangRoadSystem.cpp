#include <bits/stdc++.h>
// https://www.luogu.com.cn/blog/user48611/uva1494-qin-shi-huangs-national-road-system
constexpr int MAXN = 1e3 + 3;
constexpr int MAXM = 2e6 + 6;

using namespace std;

int testCase, n, tot, f[MAXN][11];
double sum, val[MAXN][11], ans;
array<int, MAXN> x, y, p, fa, depth;
vector<pair<double, pair<int, int>>> vec;
vector<vector<pair<int, double>>> G;

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) fa[r1] = r2;
}

inline void kruskal() {
    sort(vec.begin(), vec.end());  //按first关键值排序
    for (int i = 0, cnt = 0; i < vec.size(); i++) {
        int from = vec[i].second.first, to = vec[i].second.second;
        if (find(from) != find(to)) {
            Union(from, to);
            cnt++, sum += vec[i].first;
            G[from].push_back(make_pair(to, vec[i].first));  //建图
            G[to].push_back(make_pair(from, vec[i].first));  //无向图，加双向边
        }
        if (cnt == n - 1) return;
    }
}

inline void dfs(int cur, int fa, double w) {
    depth[cur] = depth[fa] + 1;
    f[cur][0] = fa, val[cur][0] = w;  // 0级祖先为fa, 边的值存在val[cur][0]
    for (int i = 1; i <= 10; i++)
        f[cur][i] = f[f[cur][i - 1]][i - 1],
        val[cur][i] = max(val[cur][i - 1], val[f[cur][i - 1]][i - 1]);
    for (auto e : G[cur]) {
        int to = e.first;
        double w = e.second;
        if (to != fa) dfs(to, cur, w);
    }
}

inline double LCA(int u, int v, double Max) {  // LCA模板 返回u, v间的最大边长
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = 10; i >= 0; i--)  //枚举i级祖先
        if (depth[f[u][i]] >= depth[v]) {
            Max = max(Max, val[u][i]);
            u = f[u][i];  // u向上跳
        }
    if (u == v) return Max;
    for (int i = 10; i >= 0; i--)  //枚举i级祖先
        if (f[u][i] != f[v][i]) {
            Max = max(Max, max(val[u][i], val[v][i]));
            u = f[u][i], v = f[v][i];  // u, v向上跳 直至找到公共祖先前一个位置
        }
    return max(Max, max(val[u][0], val[v][0]));
}

int main() {
    cin >> testCase;
    while (testCase--) {
        sum = ans = .0;
        vec.clear(), G.clear();
        scanf("%d", &n);
        G.resize(n + 1);  // vector建图存边……
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &x[i], &y[i], &p[i]), fa[i] = i, depth[i] = 0;
        for (int i = 1; i < n; i++)
            for (int j = i + 1; j <= n; j++) {
                double w = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
                vec.push_back(make_pair(w, make_pair(i, j)));  //存边
            }
        kruskal();     //最小生成树建图
        dfs(1, 0, 0);  //转换为以0为根的有根树 并进行LCA预处理
        for (int i = 0; i < vec.size(); i++) {  //枚举每条边
            int u = vec[i].second.first, v = vec[i].second.second;
            double w = vec[i].first;
            int A = p[u] + p[v];
            ans = max(ans, A / (sum - LCA(u, v, 0)));
        }
        printf("%.2f\n", ans);
    }
    return 0;
}