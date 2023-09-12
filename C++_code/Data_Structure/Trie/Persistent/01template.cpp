#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4735
constexpr int MAXN = 3e5 + 5;
constexpr int BIT = 24;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Trie {
    Trie *son[2];
    int lst;
} Tree[MAXN * BIT << 2], *root[MAXN << 1];
using Node = Trie *;
int n, m, preXor[MAXN << 1];
inline Node newNode(Node &root) {
    static int nptr;
    return root = &Tree[++nptr];
}
inline void insert(Node pre, Node root, int x, int Index) {
    for (int i = BIT - 1, tmp; ~i; i--) {
        tmp = (x >> i) & 1;
        if (pre) root->son[tmp ^ 1] = pre->son[tmp ^ 1];
        root->lst = max(root->lst, Index);
        root = newNode(root->son[tmp]), pre = pre ? pre->son[tmp] : NULL;
    }
    root->lst = max(root->lst, Index);
}
inline int search(Node root, int x, int limit) {
    for (int i = BIT - 1, tmp; ~i; i--) {
        tmp = (x >> i) & 1;
        if (root->son[tmp ^ 1] && root->son[tmp ^ 1]->lst >= limit) 
            root = root->son[tmp ^ 1];
        else root = root->son[tmp];
    }
    return preXor[root->lst] ^ x;
}
int main() {
    read(n), read(m);
    insert(Tree, newNode(root[0]), 0, 0);
    for (int i = 1, tmp; i <= n; i++) {
        read(tmp);
        preXor[i] = preXor[i - 1] ^ tmp;
        insert(root[i - 1], newNode(root[i]), preXor[i], i);
    }
    char type[2];
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        scanf("%s", type);
        if (type[0] == 'A') {
            read(x), n++;
            preXor[n] = preXor[n - 1] ^ x;
            insert(root[n - 1], newNode(root[n]), preXor[n], n);
        } else {
            read(l), read(r), read(x);
            printf("%d\n", search(root[r - 1], preXor[n] ^ x, l - 1));
        }
    }
    return 0;
}