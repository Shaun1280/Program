#include <bits/stdc++.h>
//求所有生成树中最大边权与最小边权差最小的 enum
const int MAXN = 1e2 + 2;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node {
    int from, to, dis;
};
inline bool cmp(const node &a, const node &b) { return a.dis < b.dis; }
node tmp;
vector<node> Edge;
int Fa[1000];
int n, m;
inline int find(int x) { return Fa[x] == x ? x : Fa[x] = find(Fa[x]); }
inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if (r1 != r2) Fa[r2] = r1;
}
inline int kruskal(int start, int cnt) {
    int maxEdge = 0, minEdge = 0x7fffffff;
    for (int i = 0; i < MAXN; i++) Fa[i] = i;
    for (int i = start; i < m; i++) {
        if (find(Edge[i].from) != find(Edge[i].to)) {
            Union(Edge[i].from, Edge[i].to);
            cnt++;
            if (cnt == n - 1) {
                maxEdge = max(maxEdge, Edge[i].dis);
                break;
            }
        }
    }
    return maxEdge;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    while (true) {
        int Min = 0x7fffffff;
        n = read(), m = read();
        if (!n && !m) break;
        Edge.clear();
        for (int i = 0; i < m; i++) {
            tmp.from = read(), tmp.to = read(), tmp.dis = read();
            Edge.push_back(tmp);
        }
        sort(Edge.begin(), Edge.end(), cmp);
        for (int i = 0; i <= m - n + 2; i++)
            if (kruskal(i, 0)) Min = min(Min, kruskal(i, 0) - Edge[i].dis);
        printf("%d\n", Min == 0x7fffffff ? -1 : Min);
    }
    return 0;
}