#include <bits/stdc++.h>
// 牛客多校第八场 https://ac.nowcoder.com/acm/contest/11259/F
// 分治 bfs 单向边 需要建立返图

using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 5e5 + 5, INF = 1e9 + 7;

struct Query { int x1, y1, x2, y2, id; } query[MAXN], q1[MAXN], q2[MAXN];

struct Edge {
    Edge() = default;
    Edge(int _to, int _next) : to(_to), next(_next) {}
    int to, next;
};

Edge e[MAXN], reve[MAXN];

int n, m, Q, ans[MAXN], dis[MAXN], vis[MAXN], revdis[MAXN];
int getx[MAXN], gety[MAXN];
int head[MAXN], revhead[MAXN];
char mp[505][505];
int id[505][505];

void add(int u, int v) {
    static int tot1 = 0, tot2 = 0;
    e[tot1].to = v, e[tot1].next = head[u], head[u] = tot1++;
    reve[tot2].to = u, reve[tot2].next = revhead[v], revhead[v] = tot2++;
}

bool inBound(int id, int lx, int rx, int ly, int ry) {
    int x = getx[id], y = gety[id];
    return lx <= x && x <= rx && ly <= y && y <= ry;
}

// 处理中线上的点 (x, y) 到其它点的最短路
void bfs(int lx, int rx, int ly, int ry, int x, int y, int* head, int* dis, Edge* edge) {
    static queue<int> q;
    for (int i = lx; i <= rx; i++)
        for (int j = ly; j <= ry; j++)
            dis[id[i][j]] = INF, vis[id[i][j]] = 0;
    dis[id[x][y]] = 0, vis[id[x][y]] = true;
    q.push(id[x][y]);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; ~i; i = edge[i].next) {
            int to = edge[i].to;
            if (inBound(to, lx, rx, ly, ry) && !vis[to]) {
                dis[to] = dis[cur] + 1;
                q.push(to);
                vis[to] = true;
            }
        }
    }
}

// ((lx, rx), (ly, ry)) 为当前矩形 ql, qr 为询问范围
void solve(int lx, int rx, int ly, int ry, int ql, int qr) {
    if (ql > qr) return;
    if (lx == rx && ly == ry) {
        for (int i = ql; i <= qr; i++) ans[query[i].id] = 0;
        return;
    }
    if (rx - lx >= ry - ly) { // 选择 x 进行划分
        int mid= (lx + rx) >> 1;
        for (int y = ly; y <= ry; y++) { // 枚举中线上的点
            bfs(mid, rx, ly, ry, mid, y, head, dis, e);
            bfs(lx, mid, ly, ry, mid, y, revhead, revdis, reve);
            for (int i = ql; i <= qr; i++) {
                int x1 = query[i].x1, y1 = query[i].y1;
                int x2 = query[i].x2, y2 = query[i].y2;
                if (x1 <= mid && mid <= x2 && y1 <= y && y <= y2) {
                    ans[query[i].id] = min(ans[query[i].id], revdis[id[x1][y1]] + dis[id[x2][y2]]);
                }
            }
        }
        int top1 = 0, top2 = 0; // 将不跨过中线的点分治处理
        for (int i = ql; i <= qr; i++) {
            int x1 = query[i].x1, y1 = query[i].y1;
            int x2 = query[i].x2, y2 = query[i].y2;
            if (inBound(id[x1][y1], lx, mid, ly, ry) && inBound(id[x2][y2], lx, mid, ly, ry))
                q1[++top1] = query[i];
            if (inBound(id[x1][y1], mid + 1, rx, ly, ry) && inBound(id[x2][y2], mid + 1, rx, ly, ry))
                q2[++top2] = query[i];
        }
        for (int i = ql; i <= ql + top1 - 1; i++) query[i] = q1[i - ql + 1];
        for (int i = ql + top1; i <= ql + top1 + top2 - 1; i++)
            query[i] = q2[i - ql - top1 + 1];
        solve(lx, mid, ly, ry, ql, ql + top1 - 1);
        solve(mid + 1, rx, ly, ry, ql + top1, ql + top1 + top2 - 1);
    } else { // 选择 y 进行划分
        int mid = (ly + ry) >> 1;
        for (int x = lx; x <= rx; x++) { // 枚举中线上的点
            bfs(lx, rx, mid, ry, x, mid, head, dis, e);
            bfs(lx, rx, ly, mid, x, mid, revhead, revdis, reve);
            for (int i = ql; i <= qr; i++) {
                int x1 = query[i].x1, y1 = query[i].y1;
                int x2 = query[i].x2, y2 = query[i].y2;
                if (y1 <= mid && mid <= y2 && x1 <= x && x <= x2) {
                    ans[query[i].id] = min(ans[query[i].id], revdis[id[x1][y1]] + dis[id[x2][y2]]);
                }
            }
        }
        int top1 = 0, top2 = 0; // 将不跨过中线的点分治处理
        for (int i = ql; i <= qr; i++) {
            int x1 = query[i].x1, y1 = query[i].y1;
            int x2 = query[i].x2, y2 = query[i].y2;
            if (inBound(id[x1][y1], lx, rx, ly, mid) && inBound(id[x2][y2], lx, rx, ly, mid))
                q1[++top1] = query[i];
            if (inBound(id[x1][y1], lx, rx, mid + 1, ry) && inBound(id[x2][y2], lx, rx, mid + 1, ry))
                q2[++top2] = query[i];
        }
        for (int i = ql; i <= ql + top1 - 1; i++) query[i] = q1[i - ql + 1];
        for (int i = ql + top1; i <= ql + top1 + top2 - 1; i++)
            query[i] = q2[i - ql - top1 + 1];
        solve(lx, rx, ly, mid, ql, ql + top1 - 1);
        solve(lx, rx, mid + 1, ry, ql + top1, ql + top1 + top2 - 1);
    }
}

void initgraph() {
    memset(head, -1, sizeof(head));
    memset(revhead, -1, sizeof(revhead));
    for (int i = 1; i <= n; i++) {
        cin.ignore(1, '\n');
        for (int j = 1; j <= m; j++) {
            id[i][j] = (i - 1) * m + j;
            cin >> mp[i][j], getx[id[i][j]] = i, gety[id[i][j]] = j;
        }
            
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == '0') {
                if (mp[i][j + 1] == '0') add(id[i][j], id[i][j + 1]);
                if (mp[i + 1][j] == '0') add(id[i][j], id[i + 1][j]);
            }
        }
}

int main() {
    boost;
    cin >> n >> m;
    initgraph();
    cin >> Q;
    int tot(0);
    for (int i = 1, type, x1, y1, x2, y2; i <= Q; i++) {
        cin >> type >> x1 >> y1 >> x2 >> y2;
        ans[i] = INF;
        if (type == 3) {
            if (x1 <= x2 && y1 <= y2) query[++tot] = (Query) {x1, y1, x2, y2, i};
        } else if (type == 2) {
            bool ok = true;
            if (x1 != x2 || y1 > y2) ok = false;
            for (int i = y1; i <= y2; i++) if (mp[x1][i] == '1') ok = false;
            if (ok) ans[i] = 0;
        } else if (type == 1) {
            bool ok = true;
            if (y1 != y2 || x1 > x2) ok = false;
            for (int i = x1; i <= x2; i++) if (mp[i][y1] == '1') ok = false;
            if (ok) ans[i] = 0;
        }
    }
    if (tot) solve(1, n, 1, m, 1, tot);
    for (int i = 1; i <= Q; i++) {
        cout << (ans[i] < INF ? "yes" : "no") << "\n";
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */