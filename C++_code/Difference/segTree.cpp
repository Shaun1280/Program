#include<bits/stdc++.h>
using namespace std;
#define int long long 
//P1438 无聊的数列
const int MAXN = 1e5 + 5;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct Node{
    int l, r, sum, add;
}Tree[MAXN << 2];
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
inline void update(int node){
    Tree[node].sum = Tree[L(node)].sum + Tree[R(node)].sum;
}
inline void pushTag(int node){
    if(!Tree[node].add) return;
    int l = Tree[node].l, r = Tree[node].r;
    int mid = (l + r) >> 1;
    Tree[L(node)].add += Tree[node].add;
    Tree[R(node)].add += Tree[node].add;
    Tree[L(node)].sum += Tree[node].add * (mid - l + 1);
    Tree[R(node)].sum += Tree[node].add * (r - mid);
    Tree[node].add = 0;
}
inline void build(int L, int R, int node){
    Tree[node].l = L, Tree[node].r = R;
    if(L == R){
        Tree[node].sum = 0;
        return;
    }
    int mid = (L + R) >> 1;
    build(L, mid, L(node));
    build(mid + 1, R, R(node));
    update(node);
}
inline void rangeChange(int L, int R, int val, int node){
    if(Tree[node].l == L && Tree[node].r == R){
        Tree[node].sum += val * (R - L + 1);
        Tree[node].add += val;
        return;
    }
    pushTag(node);
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(R <= mid) rangeChange(L, R, val, L(node));
    else if(L > mid) rangeChange(L, R, val, R(node));
    else rangeChange(L, mid, val, L(node)), rangeChange(mid + 1, R, val, R(node));
    update(node);
}
inline int ask_sum(int L, int R, int node){
    if(Tree[node].l == L && Tree[node].r == R){
        return Tree[node].sum;
    }
    pushTag(node);
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(R <= mid) return ask_sum(L, R, L(node));
    else if(L > mid) return ask_sum(L, R, R(node));
    else return ask_sum(L, mid, L(node)) + ask_sum(mid + 1, R, R(node));
}
int n, m, a[MAXN];
signed main(){
    n = read(), m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    build(1, n + 1, 1);
    while (m--){
        int type, l, r, k, d, p;
        type = read();
        if(type == 1){
            l = read(), r = read(), k = read(), d = read();
            rangeChange(l, l, k - d, 1), rangeChange(r + 1, r + 1, -(k + (r - l) * d), 1);
            rangeChange(l, r, d, 1);
        } else{
            p = read();
            printf("%lld\n", a[p] + ask_sum(1, p, 1));
        }
    }
    return 0;
}