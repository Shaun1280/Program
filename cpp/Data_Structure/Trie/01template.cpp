#include<bits/stdc++.h>
constexpr int MAXN = 1e5 + 5;
/*
https://www.luogu.com.cn/problem/P4551
1.先进行一次深度优先遍历，求出Xor[x] = Xor[fa[x]] xor Weight

从x到y路径上的所有边权异或后的值为Xor[x] ^ Xor[y]

(同一条边异或两次结果不变, x到根和y到根的重叠部分抵消掉)

于是问题化为求max(Xor[i] ^ Xor[j]), i, j ∈[1,n], 可以trie树解决The xor largest pair
*/
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? - 1: 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

vector< pair<int, int> > G[MAXN];
struct Trie {
    Trie * son[2];
} Tree[MAXN << 5];

using Node = Trie *;

int n, ans, dis[MAXN];
inline Node newNode(Node &root) {
    static int nptr;
    if (root == NULL) root = &Tree[++nptr];
    return root;
}

inline void insert(Node root, int x) {
    for (int i = 31, tmp; ~i; i--) {
        tmp = (x >> i) & 1;
        root = newNode(root->son[tmp]);
    }
}

inline void search(Node root, int x) {
    int res = 0;
    for (int i = 31, tmp; ~i; i--) {
        tmp = (x >> i) & 1;
        if (root->son[tmp ^ 1]) root = root->son[tmp ^ 1], res |= (1 << i);
        else root = root->son[tmp];
    }
    ans = max(ans, res);
}

inline void dfs(int cur, int fa) {
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (to == fa) continue;
        dis[to] = dis[cur] ^ w;
        dfs(to, cur);
    }
}

int main() {
    read(n);
    for (int i = 1, u, v, w; i < n; i++) {
        read(u), read(v), read(w);
        G[u].emplace_back(make_pair(v, w));
        G[v].emplace_back(make_pair(u, w));
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        insert(Tree, dis[i]), search(Tree, dis[i]);
    cout << ans << endl;
    return 0;
}