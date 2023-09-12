#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2805 P2805 [NOI2009]植物大战僵尸
using namespace std;

constexpr int MAXN = 5e5 + 5;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    Edge() = default;
    Edge(int _to, int _c, int _next) : to(_to), c(_c), next(_next) {}
    /*@param c capacity*/
    int to, c, next;
} edge[MAXN];
int n, m, s, t, ans;
array<int, MAXN> head, curv, depth, in, score;

inline void addEdge(int from, int to, int c) {
    static int tot;
    edge[tot] = Edge(to, c, head[from]), head[from] = tot++;
    edge[tot] = Edge(from, 0, head[to]), head[to] = tot++;
}

inline bool bfs() {
    fill(depth.begin(), depth.end(), 0);
    copy(head.begin(), head.end(), curv.begin());
    queue<int> q;
    q.push(s), depth[s] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; ~i; i = edge[i].next) {
            int to = edge[i].to;
            if (!edge[i].c || depth[to]) continue;
            depth[to] = depth[cur] + 1;
            q.push(to);
            if (to == t) return true;
        }
    }
    return false;
}

int dinic(int cur, int limit) {
    if (cur == t) return limit;
    int flow(0);
    for (int i = curv[cur]; ~i; i = edge[i].next) {
        curv[cur] = i;
        int to = edge[i].to;
        if (edge[i].c && depth[to] == depth[cur] + 1) {
            int k = dinic(to, min(edge[i].c, limit));
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
        }
    }
    if (flow == 0) depth[cur] = 0;
    return flow;
}

vector<int> G[MAXN];
inline void topoSort() {
    queue<int> q;
    for (int i = 1; i <= n * m; i++)
        if (!in[i]) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& to : G[cur])
            if (!(--in[to])) q.push(to);
    }
}
//最大闭合子图权值 = Σ正点权值-最小割
int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    fill(head.begin(), head.end(), -1);
    cin >> n >> m, s = 0, t = n * m + 1;
    for (int i = 1, cnt; i <= n * m; i++) {
        cin >> score[i] >> cnt;
        for (int j = 0, r, c; j < cnt; j++) {
            cin >> r >> c;
            G[i].push_back(r * m + c + 1); //i 能保护(r, c)的植物
            in[r * m + c + 1]++;    //(r, c) 入度加 1
        }
    }
    for (int r = 0; r < n; r++) {   //从每行最后一列开始连边
        int i = (r + 1) * m - 1;    //最后一列编号
        for (; i >= r * m + 1; i--) G[i + 1].push_back(i), in[i]++; 
        //前一列植物能保护后一列植物
    }
    topoSort(); //拓扑排序求环
    for (int i = 1; i <= n * m; i++) {
        if (in[i]) continue;  //环上的植物跳过
        if (score[i] > 0) ans += score[i], addEdge(s, i, score[i]);
        else addEdge(i, t, -score[i]);  //负权值向汇点连边
        for (auto& to : G[i]) { //for i 能保护得植物
            if (in[to]) continue;   //环上的植物跳过
            addEdge(to, i, INF);    //要攻击 to 就要先攻击 i
        }
    }
    while(bfs()) ans -= dinic(s, INF);
    cout << ans << endl;
    return 0;
}