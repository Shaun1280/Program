#include <bits/stdc++.h>
//骑马修栅栏 Riding the Fences
constexpr int MAXM = 1 << 11;

#define pii pair<int, int>

using namespace std;

struct node {
    int to, next, vis;
    node() {}
    node(int _to, int _next, int _vis) { to = _to, next = _next, vis = _vis; }
};
vector<node> Edge;
vector<int> vec;

int n, tot, head[MAXM], degree[MAXM], maxn;
inline void add(int from, int to) {
    Edge.push_back(node(to, head[from], false)), head[from] = tot++;
    Edge.push_back(node(from, head[to], false)), head[to] = tot++;
}

void dfs(int cur) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        if (Edge[i].vis) continue;
        q.push(make_pair(Edge[i].to, i));
    }
    while (!q.empty()) {
        int to = q.top().first, i = q.top().second;
        q.pop();
        if (Edge[i].vis) continue;
        Edge[i].vis = Edge[i ^ 1].vis = true;
        dfs(to);
    }
    vec.push_back(cur);
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        maxn = max(maxn, max(u, v));
        degree[u]++, degree[v]++;
    }
    int st = 1;
    for (int i = 1; i <= maxn; i++) {
        if (degree[i] & 1) {
            st = i;
            break;
        }
    }
    dfs(st);
    for (int i = (int)vec.size() - 1; i >= 0; i--) printf("%d\n", vec[i]);
    return 0;
}