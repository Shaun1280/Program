#include <bits/stdc++.h>
// 分治最短路
// https://www.luogu.com.cn/problem/P3350 [ZJOI2016]旅行者

using namespace std;

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

constexpr int MAXN = 2e4 + 4, INF = 1e9 + 7;

struct Query { int x1, y1, x2, y2, id; } query[MAXN * 5], q1[MAXN * 5], q2[MAXN * 5];

int n, m, Q, ans[MAXN * 5], dis[MAXN * 5], vis[MAXN * 5];
int getx[MAXN * 5], gety[MAXN * 5];
vector<pair<int, int>> g[MAXN], revg[MAXN];

int id(int i, int j) { return (i - 1) * m + j; }
void add(int u, int v, int w) { g[u].emplace_back(v, w), g[v].emplace_back(u, w); }

bool inBound(int id, int lx, int rx, int ly, int ry) {
    int x = getx[id], y = gety[id];
    return lx <= x && x <= rx && ly <= y && y <= ry;
}

// 处理中线上的点 (x, y) 到其它点的最短路
void dijkstra(int lx, int rx, int ly, int ry, int x, int y) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for (int i = lx; i <= rx; i++)
        for (int j = ly; j <= ry; j++)
            dis[id(i, j)] = INF, vis[id(i, j)] = 0;
    dis[id(x, y)] = 0;
    q.emplace(0, id(x, y));
    while (!q.empty()) {
        int dist, cur, to, w;
        tie(dist, cur) = q.top();
        q.pop();
        if (vis[cur]) continue;
        for (auto& e : g[cur]) {
            to = e.first, w = e.second;
            if (inBound(to, lx, rx, ly, ry) && dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w;
                q.emplace(dis[to], to);
            }
        }
        vis[cur] = true;
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
            dijkstra(lx, rx, ly, ry, mid, y);
            for (int i = ql; i <= qr; i++) {
                int x1 = query[i].x1, y1 = query[i].y1;
                int x2 = query[i].x2, y2 = query[i].y2;
                ans[query[i].id] = min(ans[query[i].id], dis[id(x1, y1)] + dis[id(x2, y2)]);
            }
        }
        int top1 = 0, top2 = 0; // 将不跨过中线的点分治处理
        for (int i = ql; i <= qr; i++) {
            int x1 = query[i].x1, y1 = query[i].y1;
            int x2 = query[i].x2, y2 = query[i].y2;
            if (inBound(id(x1, y1), lx, mid, ly, ry) && inBound(id(x2, y2), lx, mid, ly, ry))
                q1[++top1] = query[i];
            if (inBound(id(x1, y1), mid + 1, rx, ly, ry) && inBound(id(x2, y2), mid + 1, rx, ly, ry))
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
            dijkstra(lx, rx, ly, ry, x, mid);
            for (int i = ql; i <= qr; i++) {
                int x1 = query[i].x1, y1 = query[i].y1;
                int x2 = query[i].x2, y2 = query[i].y2;
                ans[query[i].id] = min(ans[query[i].id], dis[id(x1, y1)] + dis[id(x2, y2)]);
            }
        }
        int top1 = 0, top2 = 0; // 将不跨过中线的点分治处理
        for (int i = ql; i <= qr; i++) {
            int x1 = query[i].x1, y1 = query[i].y1;
            int x2 = query[i].x2, y2 = query[i].y2;
            if (inBound(id(x1, y1), lx, rx, ly, mid) && inBound(id(x2, y2), lx, rx, ly, mid))
                q1[++top1] = query[i];
            if (inBound(id(x1, y1), lx, rx, mid + 1, ry) && inBound(id(x2, y2), lx, rx, mid + 1, ry))
                q2[++top2] = query[i];
        }
        for (int i = ql; i <= ql + top1 - 1; i++) query[i] = q1[i - ql + 1];
        for (int i = ql + top1; i <= ql + top1 + top2 - 1; i++)
            query[i] = q2[i - ql - top1 + 1];
        solve(lx, rx, ly, mid, ql, ql + top1 - 1);
        solve(lx, rx, mid + 1, ry, ql + top1, ql + top1 + top2 - 1);
    }
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1, r; j < m; j++) {
            read(r);
            add(id(i, j), id(i, j + 1), r);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1, c; j <= m; j++) {
            read(c);
            add(id(i, j), id(i + 1, j), c);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            getx[id(i, j)] = i, gety[id(i, j)] = j;
    read(Q);
    for (int i = 1; i <= Q; i++) {
        read(query[i].x1, query[i].y1, query[i].x2, query[i].y2);
        query[i].id = i;
        ans[i] = INF;
    }
    solve(1, n, 1, m, 1, Q);
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */