#include <bits/stdc++.h>
// P2325 [SCOI2005]王室联邦 dfs 栈 树分块
using namespace std;
// https://shaun-shane.vercel.app/2020/09/05/Mo-s-Algorithm-on-tree/#p2325-scoi2005%E7%8E%8B%E5%AE%A4%E8%81%94%E9%82%A6
constexpr int MAXN = 1e3 + 3;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, b, ans;
array<int, MAXN> belong, pro;
vector<int> G[MAXN];

stack<int> s;
void dfs(int cur, int fa) {
    int tmp = s.size();
    for (auto& to : G[cur]) {
        if (to == fa) continue;
        dfs(to, cur);
        if (static_cast<int>(s.size()) - tmp >= b) {  //块的大小 >= b
            pro[++ans] = cur;
            while (s.size() > tmp) belong[s.top()] = ans, s.pop();
        }
    }
    s.push(cur);
}

int main() {
    read(n), read(b);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    if (!ans) pro[++ans] = 1;
    while (!s.empty()) belong[s.top()] = ans, s.pop();
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) printf("%d ", belong[i]);
    printf("\n");
    for (int i = 1; i <= ans; i++) printf("%d ", pro[i]);
    return 0;
}