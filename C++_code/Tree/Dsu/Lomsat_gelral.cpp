#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/CF600E
//https://shaun118294191.github.io/post/cf600e-lomsat-gelral/
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
 
constexpr int MAXN = 1e5 + 5;
using A = long long [MAXN];
 
int n;
A son, father, sz, cnt, color, res, maxCnt;
vector<int> G[MAXN];
 
inline void Init(int cur, int fa) {
    father[cur] = fa, son[cur] = 0, sz[cur] = 1;
    for (auto &to : G[cur]) {
        if (to == fa) continue;
        Init(to, cur);
        sz[cur] += sz[to];
        if (!son[cur] || sz[son[cur]] < sz[to])
            son[cur] = to;
    }
}
 
inline void compare(int cur, int col) {
    if (cnt[col] > maxCnt[cur]) {
        res[cur] = col;
        maxCnt[cur] = cnt[col];
    } else if (cnt[col] == maxCnt[cur]) res[cur] += col;
}
 
inline void add(int fa, int cur, int val) {
    cnt[color[cur]] += val, compare(fa, color[cur]);
    for (auto &to : G[cur]) {
        if (to == father[cur] || to == son[fa]) continue; //to不是父亲节点且不是重儿子
        add(fa, to, val);
    }
}

inline void dfs(int cur, bool keep) {
    for (auto &to : G[cur]) {
        if (to == father[cur] || to == son[cur]) continue;
        dfs(to, false); //递归处理轻儿子
    }
    if (son[cur]) dfs(son[cur], true); //递归处理重儿子
    res[cur] = res[son[cur]], maxCnt[cur] = maxCnt[son[cur]]; //保存重儿子已统计的信息
    add(cur, cur, 1);
    if (keep == false) son[cur] = 0, add(cur, cur, -1);
                    //为将轻儿子子树(包括重儿子)清空, son[cur] 赋为0;
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(color[i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    Init(1, 0);
    dfs(1, true);
    for (int i = 1; i <= n; i++) printf("%lld ", res[i]);
    return 0;
}