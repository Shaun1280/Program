#include <bits/stdc++.h>
//https://shaunshane.gitee.io/2020/04/26/Island/
constexpr int MAXN = 1e6 + 6;
using namespace std;
using LL = long long;
using Arr = LL[MAXN];

LL n, ans;
Arr in, dis, diameter, belong, tmpDis, cycleDis;
vector<pair<int, int> > G[MAXN];

inline void bfs(int cur, int cnt) { //bfs处理出该节点属于哪一个基环树
    queue<int> q;
    q.push(cur);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        belong[cur] = cnt;
        for (auto& e : G[cur]) {
            int to = e.first;
            if (!belong[to]) q.push(to);
        }
    }
}

inline void topoSort() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (in[i] == 1) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& e : G[cur]) {
            int to = e.first, w = e.second;
            if (in[to] > 1) {
                in[to]--;
                diameter[belong[to]] =
                    max(diameter[belong[to]], dis[to] + dis[cur] + w);
                dis[to] = max(dis[to], dis[cur] + w);
                //dp求直径与以环结点为起点的子树中的最长链
                if (in[to] == 1) q.push(to);
            }
        }
    }
}

inline void dp(int cur, int cnt, LL res) {
    int st = cur, end = false, m(0);
    res = diameter[cnt];
    do {
        end = true, in[cur] = 1;
        tmpDis[++m] = dis[cur]; //根到节点的最长距离
        for (auto& e : G[cur]) {
            int to = e.first, w = e.second;
            if (in[to] <= 1) continue;
            end = false, cur = to;
            cycleDis[m + 1] = cycleDis[m] + w;
            break;
        }
    } while (!end);
    for (auto& e : G[cur]) { //回到起点
        int to = e.first, w = e.second;
        if (to == st) cycleDis[m + 1] = cycleDis[m] + w;
    }
    for (int i = 1; i < m; i++) {//断环成链 复制一倍
        tmpDis[i + m] = tmpDis[i];
        cycleDis[i + m] = cycleDis[m + 1] + cycleDis[i];
    }
    deque<int> q;
    q.push_back(1);
    for (int i = 2; i < 2 * m; i++) {
        while (!q.empty() && i - q.front() >= m) q.pop_front();
        res = max(res, tmpDis[i] + tmpDis[q.front()] + cycleDis[i] -
                           cycleDis[q.front()]);
        //让tmpDis[q.front()] + cycleDis[q.front()]单调递增
        while (!q.empty() &&
               tmpDis[i] - cycleDis[i] >= tmpDis[q.back()] - cycleDis[q.back()])
            q.pop_back(); //比当前值小则无效，直接弹出
        q.push_back(i);
    }
    ans += res;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int u = 1, v, w; u <= n; u++) {
        cin >> v >> w;
        G[u].emplace_back(make_pair(v, w));
        G[v].emplace_back(make_pair(u, w));
        in[u]++, in[v]++;
    }
    int cnt(0);
    for (int i = 1; i <= n; i++)
        if (!belong[i]) bfs(i, ++cnt);
    topoSort();
    for (int i = 1; i <= n; i++)
        if (in[i] > 1) dp(i, belong[i], 0);
    cout << ans << endl;
    return 0;
}