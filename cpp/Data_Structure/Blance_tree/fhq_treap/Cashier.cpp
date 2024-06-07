#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1486
//P1486 [NOI2004]郁闷的出纳员
constexpr int MAXN = 2e5 + 5;
using namespace std;
using LL = long long;
template <typename T>
inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct Treap {
    Treap *lson, *rson;
    LL key; 
    int size, priority, tag;
}Tree[MAXN], *root;
using Node = Treap*;
#define Lson root->lson
#define Rson root->rson
int n, tot, leave, Min;
inline void newNode(Node &root, int key) {
    root = &Tree[++tot], root->size = 1;
    root->key = key, root->priority = rand();
}
inline void update(Node root) {
    int Lsize = Lson ? Lson->size : 0, Rsize = Rson ? Rson->size : 0;
    root->size = Lsize + Rsize + 1;
}
inline void pushTag(Node root) {
    if (!root->tag) return;
    if (Lson) Lson->tag += root->tag, Lson->key += root->tag;
    if (Rson) Rson->tag += root->tag, Rson->key += root->tag;
    root->tag = 0;
}
inline void split(Node root, Node &L, Node &R, LL key) {
    if (root == NULL) {
        L = R = NULL;
        return;
    }
    pushTag(root);
    if (root->key <= key) L = root, split(Rson, Rson, R, key);
    else R = root, split(Lson, L, Lson, key);
    update(root);
}
inline void merge(Node &root, Node L, Node R) {
    if (L == NULL) {root = R; return;}
    if (R == NULL) {root = L; return;}
    if (L->priority < R->priority) pushTag(root = L), merge(Rson, Rson, R);
    else pushTag(root = R), merge(Lson, L, Lson);
    update(root);
}
inline LL getKth(Node root, int rank) {
    if (root == NULL) return -1;
    pushTag(root);
    int Rsize = Rson ? Rson->size : 0;
    if (Rsize >= rank) return getKth(Rson, rank);
    if (Rsize + 1 == rank) return root->key; 
    return getKth(Lson, rank - Rsize - 1);
}
inline void insert(Node &root, LL key) {
    if (key < Min) return;
    Node L = NULL, R = NULL, tmp = NULL;
    newNode(tmp, key);
    split(root, L, R, key);
    merge(L, L, tmp), merge(root, L, R);
}
inline void remove(Node &root, LL key) {
    Node L = NULL, R = NULL, tmp = NULL;
    split(root, L, R, key - 1);
    leave += L ? L->size : 0;
    merge(root, tmp, R);
}
int main() {
    read(n), read(Min);
    for (int i = 1; i <= n; i++) {
        char s; int k;
        cin >> s; read(k);
        if (s == 'I') insert(root, k); 
        else if (s == 'A') root->key += k, root->tag += k;
        else if (s == 'S') {
            root->key -= k, root->tag -= k;
            remove(root, Min);
        }
        else printf("%lld\n", getKth(root, k));
    }
    printf("%d\n", leave);
    return 0;
}