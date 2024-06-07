#include<bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/P2894
//P2894 [USACO08FEB]酒店Hotel
const int MAXN = 1e5 + 5;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct Node{
    int l, r;
    int maxPre, maxSuf;
    int sum, add;
}Tree[MAXN << 2];
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
#define sz(x) (Tree[x].r - Tree[x].l + 1)
inline void update(int node){
    if(Tree[L(node)].sum == sz(L(node)))
        Tree[node].maxPre = Tree[L(node)].sum + Tree[R(node)].maxPre;
    else Tree[node].maxPre = Tree[L(node)].maxPre;
    if(Tree[R(node)].sum == sz(R(node)))
        Tree[node].maxSuf = Tree[R(node)].sum + Tree[L(node)].maxSuf;
    else Tree[node].maxSuf = Tree[R(node)].maxSuf;
    Tree[node].sum = max(Tree[L(node)].maxSuf + Tree[R(node)].maxPre, max(Tree[L(node)].sum, Tree[R(node)].sum));
}
inline void pushTag(int node){
    if(!Tree[node].add) return;
    Tree[L(node)].add = Tree[R(node)].add = Tree[node].add;
    if(Tree[node].add == -1){ //Checkin
        Tree[L(node)].sum = Tree[L(node)].maxPre = Tree[L(node)].maxSuf = 0;
        Tree[R(node)].sum = Tree[R(node)].maxPre = Tree[R(node)].maxSuf = 0;
    }
    if(Tree[node].add == 1){//Checkout
        Tree[L(node)].sum = Tree[L(node)].maxPre = Tree[L(node)].maxSuf = sz(L(node));
        Tree[R(node)].sum = Tree[R(node)].maxPre = Tree[R(node)].maxSuf = sz(R(node));
    }
    Tree[node].add = 0;
}
inline void build(int L, int R, int node){
    Tree[node].l = L, Tree[node].r = R;
    Tree[node].sum = Tree[node].maxPre = Tree[node].maxSuf = R - L + 1;
    if(L == R) return;
    int mid = (L + R) >> 1;
    build(L, mid, L(node));
    build(mid + 1, R, R(node));
    update(node);
}
inline void change(int L, int R, int val, int node){
    if(Tree[node].l == L && Tree[node].r == R){
        Tree[node].sum = (val == 1 ?  val * (R - L + 1) : 0);
        Tree[node].maxPre = Tree[node].maxSuf = Tree[node].sum;
        Tree[node].add = val;
        return;
    }
    pushTag(node);
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(R <= mid) change(L, R, val, L(node));
    else if(L > mid) change(L, R, val, R(node));
    else change(L, mid, val, L(node)), change(mid + 1, R, val, R(node));
    update(node);
}
inline int query(int Len, int node){
    if(Tree[node].l == Tree[node].r) return Tree[node].l;
    pushTag(node);
    int mid = (Tree[node].l + Tree[node].r )>> 1;
    if(Tree[L(node)].sum >= Len) return query(Len, L(node));
    else if(Tree[L(node)].maxSuf + Tree[R(node)].maxPre >= Len) return mid - Tree[L(node)].maxSuf + 1;
    return query(Len, R(node));
}
int n, m;
int main(){
    n = read(), m = read();
    build(1, n, 1);
    while (m--){
        int type, x, d;
        type = read();
        if(type == 1){
            d = read();
            if(Tree[1].sum >= d){
                int L = query(d, 1);
                printf("%lld\n", L);
                change(L, L + d - 1, -1, 1);
            } 
            else puts("0");
        } else{
            x = read(), d = read();
            change(x, x + d - 1, 1, 1);
        }
    }
    return 0;
}