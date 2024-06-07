#include <bits/stdc++.h>
// SP2059 CERC07S - Robotic Sort
constexpr int MAXN = 1e5 + 5;
constexpr int Inf = 1e9;
// https://www.luogu.com.cn/problem/SP2059
using namespace std;
// https://shaun118294191.github.io/post/sp2059-cerc07s-robotic-sort/
template <typename T>
inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct Treap {
    Treap *lson, *rson;
    int size, priority;
    int key, tag, min;
} Tree[MAXN], *root, *tmp;
#define Lson root->lson
#define Rson root->rson
using Node = Treap *;
int tot, n, cnt;

inline void newNode(Node &root, int key) {
    root = &Tree[tot++], root->min = key;
    root->key = key, root->priority = rand(), root->size = 1;
}

inline void update(Node root) {
    int Lsize = Lson ? Lson->size : 0, Rsize = Rson ? Rson->size : 0;
    int Lmin = Lson ? Lson->min : Inf, Rmin = Rson ? Rson->min : Inf;
    root->size = Lsize + Rsize + 1;
    root->min = min(root->key, min(Lmin, Rmin));
}

inline void pushTag(Node root) {
    if (!root->tag) return;
    swap(Lson, Rson);
    if (Lson) Lson->tag ^= 1;
    if (Rson) Rson->tag ^= 1;
    root->tag = 0;
}

inline int getPos(Node root, int key) {
    if (root == NULL) return 0;
    pushTag(root);
    int Lsize = Lson ? Lson->size : 0;
    int Lmin = Lson ? Lson->min : Inf, Rmin = Rson ? Rson->min : Inf;
    if (root->key == key && Lmin > key)
        return Lsize + 1;
    else if (Lmin == key)
        return getPos(Lson, key);
    else
        return Lsize + 1 + getPos(Rson, key);
}

inline void split(Node root, Node &L, Node &R, int size) {
    if (root == NULL) {
        L = R = NULL;
        return;
    }
    pushTag(root);  //分裂前下放标记到左右子树
    int Lsize = Lson ? Lson->size : 0;
    if (Lsize + 1 <= size)
        L = root, split(Rson, Rson, R, size - Lsize - 1);
    else
        R = root, split(Lson, L, Lson, size);
    update(root);
}

inline void merge(Node &root, Node L, Node R) {
    if (L == NULL) {
        root = R;
        return;
    }
    if (R == NULL) {
        root = L;
        return;
    }
    if (L->priority < R->priority)
        pushTag(root = L), merge(Rson, Rson, R);
    else
        pushTag(root = R), merge(Lson, L, Lson);
    update(root);
}

pair<int, int> vec[MAXN];
int main() {
    // freopen("test.out", "w", stdout);
    srand(time(0));
    while (cin >> n && n) {
        tot = 0, root = NULL;
        memset(Tree, 0, sizeof(Tree));
        for (int i = 1, val; i <= n; i++) read(val), vec[i] = make_pair(val, i);
        sort(vec + 1, vec + n + 1);
        for (int i = 1; i <= n; i++) vec[vec[i].second].first = i;  //类似离散化
        for (int i = 1; i <= n; i++)
            newNode(tmp, vec[i].first), merge(root, root, tmp);
        for (int i = 1; i <= n; i++) {
            Node L = NULL, tmp = NULL, R = NULL;
            int pos = getPos(root, root->min);
            i == n ? printf("%d\n", pos + i - 1) : printf("%d ", pos + i - 1);
            split(root, L, R, pos - 1), split(R, tmp, R, 1);
            if (L) L->tag ^= 1;
            merge(root, L, R);
        }
    }
    return 0;
}