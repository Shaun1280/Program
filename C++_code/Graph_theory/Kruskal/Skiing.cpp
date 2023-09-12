#include <bits/stdc++.h>
// P2573 [SCOI2012]滑雪
// 1.由于题目限制，有些边不能使用，故不能直接做最小生成树。
//于是我们先建立一个图（从高的点向低的点建边，注意：当起点终点h相同时要加双向边），
//从1号点开始dfs，找到所有能到达的点，并记录各边的信息和点的个数
// 2.对合法的边进行排序，由题意，先满足访问的点最多，故按各边终点的h降序排序，
//又要满足路径长最小，故当h相同时按dis升序排序
// 3.跑一遍最小生成树即可得到答案。
#define LL long long

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}

int *Fa = NULL, *Height = NULL, *head = NULL, *vis = NULL;
int cnt, total_node;
int N, M;

struct node {
    int to, next, dis;
} *Edge = NULL;

inline void Init() {
    Fa = (int *)malloc((N + 1) * sizeof(int));
    Height = (int *)malloc((N + 1) * sizeof(int));
    head = (int *)malloc((N + 1) * sizeof(int));
    vis = (int *)malloc((N + 1) * sizeof(int));
    Edge = (node *)malloc(2 * (M + 1) * sizeof(node));
    for (int i = 0; i <= N; i++) Fa[i] = i, head[i] = -1, vis[i] = false;
    for (int i = 1; i <= N; i++) Height[i] = read();
}

inline void add_edge(int from, int to, int dis) {
    Edge[cnt].next = head[from];
    Edge[cnt].to = to, Edge[cnt].dis = dis;
    head[from] = cnt++;
}

struct edge {
    int from, to, dis;
};
edge tmp;
vector<edge> E;

inline bool cmp(const edge &a, const edge &b) {
    if (Height[a.to] == Height[b.to]) return a.dis < b.dis;
    return Height[a.to] > Height[b.to];
}

inline void dfs(int cur) {
    vis[cur] = true, total_node++;
    for (int i = head[cur]; i != -1; i = Edge[i].next) {
        int to = Edge[i].to;
        tmp.from = cur, tmp.to = to, tmp.dis = Edge[i].dis;
        E.push_back(tmp);
        if (!vis[to]) dfs(to);
    }
}

inline int find(int x) { return Fa[x] == x ? x : Fa[x] = find(Fa[x]); }

inline void Union(int from, int to) {
    int r1 = find(from), r2 = find(to);
    if (r1 != r2) Fa[r1] = r2;
}

inline void Kruskal(int Cnt, LL distance) {
    for (int i = 0; i < E.size(); i++) {
        int from = E[i].from, to = E[i].to;
        if (find(from) != find(to)) {
            Union(E[i].from, E[i].to);
            distance += E[i].dis, Cnt++;
            if (Cnt == total_node - 1) break;
        }
    }
    printf("%d %lld", Cnt + 1, distance);
}

int main() {
    N = read(), M = read();
    Init();
    int u, v, w;
    while (M--) {
        u = read(), v = read(), w = read();
        if (Height[u] >= Height[v]) add_edge(u, v, w);
        if (Height[u] <= Height[v]) add_edge(v, u, w);
    }
    dfs(1);
    sort(E.begin(), E.end(), cmp);
    Kruskal(0, 0LL);
    free(Fa), free(Height), free(Edge), free(head), free(vis);
    Fa = NULL, Height = NULL, Edge = NULL, head = NULL, vis = NULL;
    return 0;
}