#include <bits/stdc++.h>

constexpr int MAXN = 1e6 + 6;
constexpr int Inf = 2e9;

using namespace std;

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
    int key, priority;
    int size;
} Tree[MAXN], *rt;
int tot, Q, type, x;
#define Lson root->lson
#define Rson root->rson

inline void newNode(Treap *&root, int key) {
    root = &Tree[++tot], root->size = 1;
    root->key = key, root->priority = rand();
}

inline void update(Treap *root) {
    int Lsize = Lson ? Lson->size : 0, Rsize = Rson ? Rson->size : 0;
    root->size = Lsize + Rsize + 1;
}

inline void split(Treap *root, Treap *&L, Treap *&R, int key) {
    if (root == NULL) {
        L = NULL, R = NULL;
        return;
    }
    if (root->key <= key)
        L = root, split(Rson, Rson, R, key);
    else
        R = root, split(Lson, L, Lson, key);
    update(root);
}

inline void merge(Treap *&root, Treap *L, Treap *R) {
    if (L == NULL) {
        root = R;
        return;
    }
    if (R == NULL) {
        root = L;
        return;
    }
    if (L->priority < R->priority)
        root = L, merge(Rson, Rson, R);
    else
        root = R, merge(Lson, L, Lson);
    update(root);
}

inline void insert(Treap *&root, int key) {
    Treap *L = NULL, *R = NULL, *tmp = NULL;
    newNode(tmp, key);                    //新建节点
    split(root, L, R, key);               //按key分裂
    merge(L, L, tmp), merge(root, L, R);  // tmp与L合并，L与R合并
}

inline void remove(Treap *&root, int key) {
    Treap *L = NULL, *R = NULL, *tmp = NULL;
    split(root, L, R, key);
    split(L, L, tmp, key - 1);         //按key - 1分裂 tmp的值都>= key
    merge(tmp, tmp->lson, tmp->rson);  //合并lson rson，从而减去一个key值
    merge(L, L, tmp), merge(root, L, R);  //合并回root
}

inline int getVal(Treap *root, int rank) {  //排名为rank的值
    while (true) {
        if (root == NULL) return 0;
        int Lsize = Lson ? Lson->size : 0;
        if (Lsize + 1 == rank) return root->key;
        if (Lsize >= rank)
            root = Lson;
        else
            rank -= Lsize + 1, root = Rson;
    }
}

inline int getRank(Treap *&root, int key) {
    Treap *L = NULL, *R = NULL;
    split(root, L, R, key - 1);
    int res = (L ? L->size : 0) + 1;
    merge(root, L, R);
    return res;
}

inline int getPre(Treap *&root, int key) {
    Treap *L = NULL, *R = NULL;
    split(root, L, R, key - 1);
    int res = getVal(L, L->size);
    merge(root, L, R);
    return res;
}

inline int getNext(Treap *&root, int key) {
    Treap *L = NULL, *R = NULL;
    split(root, L, R, key);
    int res = getVal(R, 1);
    merge(root, L, R);
    return res;
}

int main() {
    srand(time(0));
    read(Q);
    while (Q--) {
        read(type), read(x);
        switch (type) {
            case 1:
                insert(rt, x);
                break;
            case 2:
                remove(rt, x);
                break;
            case 3:
                printf("%d\n", getRank(rt, x));
                break;
            case 4:
                printf("%d\n", getVal(rt, x));
                break;
            case 5:
                printf("%d\n", getPre(rt, x));
                break;
            case 6:
                printf("%d\n", getNext(rt, x));
                break;
        }
    }
    return 0;
}