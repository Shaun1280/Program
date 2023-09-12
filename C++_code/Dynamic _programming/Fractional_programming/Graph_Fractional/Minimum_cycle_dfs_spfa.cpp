#include <bits/stdc++.h>

const int MAXP = 3e3 + 3;
const int MAXE = 1e4 + 4;
const double EPSILON = 1e-9;

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}

struct node {
    int to, next;
    double w;
} Edge[MAXE];
int head[MAXP], vis[MAXP];
double dis[MAXE];
int n, m, tot;

inline void add_edge(int from, int to, double w) {
    Edge[tot].next = head[from];
    Edge[tot].to = to, Edge[tot].w = w;
    head[from] = tot++;
}

inline bool dfs_spfa(int cur, double x) {
    vis[cur] = true;
    for (int i = head[cur]; i != -1; i = Edge[i].next) {
        int to = Edge[i].to;
        if (dis[to] > dis[cur] + Edge[i].w - x) {
            dis[to] = dis[cur] + Edge[i].w - x;
            if (vis[to] || dfs_spfa(to, x)) return true;
            //再次被访问 说明一定有负环
        }
    }
    vis[cur] = false;  //
    return false;
}

inline bool check(double x) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; i++)
        if (dfs_spfa(i, x)) return true;
    return false;
}

inline void Binary_search(double l, double r) {
    while (l + EPSILON < r) {
        double mid = (l + r) / 2.0;
        if (check(mid)) r = mid;
        /*sigma(w[i] - 1 * x) <0 存在负环 答案偏大*/
        else
            l = mid;
    }
    printf("%.8f", l);
}

int main() {
    n = read(), m = read();
    memset(head, -1, sizeof(head));
    int u, v;
    double w;
    for (int i = 1; i <= m; i++) {
        u = read(), v = read(), scanf("%lf", &w);
        add_edge(u, v, w);
    }
    Binary_search(-1e6, 1e6);
    return 0;
}