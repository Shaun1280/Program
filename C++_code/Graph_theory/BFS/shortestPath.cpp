#include <bits/stdc++.h>
// https://www.luogu.com.cn/blog/user48611/cf59e-shortest-path
constexpr int MAXN = 3e3 + 3;
constexpr int MAXM = 2e4 + 4;
constexpr int M = 99991;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
int n, m, k, tot = 1;
int dis[MAXM << 1], pre[MAXM << 1], head[MAXN], vis[MAXM << 1];
struct triplet {  //三元组
    int a, b, c;
    triplet() {}
    triplet(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
} tmp;
struct E {  //边
    int to, next;
    E() {}
    E(int _to, int _next) : to(_to), next(_next) {}
} Edge[MAXM << 1];
inline void add(int from, int to) {
    Edge[++tot] = E(to, head[from]), head[from] = tot;
    Edge[++tot] = E(from, head[to]), head[to] = tot;
}
/******************hash********************/
vector<triplet> Hash[M + 1];
inline int getHash(triplet x) {
    return ((x.a * x.b % M * x.c % M) + x.a + x.b + x.c) % M;
}
inline void insert(triplet x) { Hash[getHash(x)].push_back(x); }
inline bool check(triplet x) {
    for (auto i : Hash[getHash(x)])
        if (x.a == i.a && x.b == i.b && x.c == i.c) return true;
    return false;
}
/*****************hash********************/
inline void print(int id) {
    if (id != 0)
        print(pre[id]), printf("%d ", Edge[id].to);
    else
        printf("1 ");
}
inline void BFS() {
    queue<pair<int, int> > q;  // first记录当前节点 second记录指向该节点的边的id
    q.push({1, 0});
    while (!q.empty()) {
        int cur = q.front().first, id = q.front().second;
        q.pop();
        for (int i = head[cur]; i; i = Edge[i].next) {
            int to = Edge[i].to;
            if (check(triplet(Edge[id ^ 1].to, cur, to)) || vis[i]) continue;
            dis[i] = dis[id] + 1, pre[i] = id, vis[i] = true;
            //到达i号边的距离 并记录i号边的前驱
            if (to == n) {
                printf("%d\n", dis[i]), print(i);
                return;
            }
            q.push({to, i});
        }
    }
    puts("-1");
}
int main() {
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read();
        add(u, v);  //建图 需成对储存 tot
    }
    for (int i = 1; i <= k; i++) {
        tmp.a = read(), tmp.b = read(), tmp.c = read();
        insert(tmp);  //插入hash表
    }
    BFS();
    return 0;
}