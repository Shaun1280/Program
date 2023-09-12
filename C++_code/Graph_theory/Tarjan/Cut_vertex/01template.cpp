#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 5;

struct Edge {
    Edge() = default;
    Edge(int _to, int _next) : to(_to), next(_next) {}
    int to, next;
};
vector<Edge> edge;
array<int, MAXN> dfn, low, head, cut, sz, ok;
int n, cntCut, tot;

inline void addEdge(int from, int to) {
    edge.emplace_back(to, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, head[to]), head[to] = edge.size() - 1;
}

void tarjan(int cur) {
    dfn[cur] = low[cur] = ++tot;
    sz[cur] = 1;
    int cnt(0);
    for (int i = head[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (!dfn[to]) { //在搜索树上
            tarjan(to);
            sz[cur] += sz[to];
            low[cur] = min(low[cur], low[to]);
            if (dfn[cur] <= low[to]) { //
                cnt++;
                if (sz[to] & 1) ok[cur] = false;
                if (cur != 1 || cnt >= 2) cut[cur] = true;  //is cut vertex
            }
        } else low[cur] = min(low[cur], dfn[to]); //不在搜索树上
    }
    if (cut[cur]) cntCut++;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    while (cin >> n && n) {
        edge.clear();
        fill(head.begin(), head.end(), -1), fill(cut.begin(), cut.end(), 0);
        fill(low.begin(), low.end(), 0), fill(dfn.begin(), dfn.end(), 0);
        fill(ok.begin(), ok.end(), 1);
        cntCut = 0, tot = 0;
        int u, v;
        while (cin >> u && u) {
            while (cin >> v) {
                addEdge(u, v);
                if (cin.get() == '\n') break;
            }
        }
        tarjan(1);
        cout << cntCut << '\n';
    }
    cout.flush();
}