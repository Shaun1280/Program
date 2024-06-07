#include<bits/stdc++.h>
//max_sequence point_change merge 
//SP1716 GSS3 - Can you answer these queries III
#define LL long long
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
const int MAXN = 5e4 + 1;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch -48, ch = getchar();
    return x * f;
}
struct Node{
    int l, r;
    LL Lmax, Rmax, Max, sum;
}Tree[MAXN << 2];
int num[MAXN];
inline Node operator + (Node Lson, Node Rson){
    Node tmp;
    tmp.l = Lson.l, tmp.r = Rson.r; //tmp的左右端点需更新并返回
    tmp.sum = Lson.sum + Rson.sum;
    tmp.Lmax = max(Lson.sum + Rson.Lmax, Lson.Lmax);
    tmp.Rmax = max(Rson.sum + Lson.Rmax, Rson.Rmax);
    tmp.Max = max(Lson.Rmax + Rson.Lmax, max(Lson.Max, Rson.Max));
    //区间左端某一段最大子段和 区间右端某一段最大子段和 左区间最靠右的一段+右区间最靠左的一段的最大值
    return tmp;
}
inline void update(int node){
    Tree[node] = Tree[L(node)] + Tree[R(node)];
    return;
}
inline void change(int pos, int val, int node){
    if(Tree[node].l == pos && Tree[node].r == pos){
        Tree[node].Lmax = Tree[node].Rmax = val;
        Tree[node].sum = Tree[node].Max = val;
        return;
    }
    int mid= (Tree[node].l + Tree[node].r) >> 1;
    if(pos <= mid) change(pos, val, L(node));
    else if(pos > mid) change(pos, val, R(node));
    update(node);
    return;
}
inline void build(int Left, int Right, int node){
    if(Left == Right){
        Tree[node].Max = Tree[node].sum = Tree[node].Lmax = Tree[node].Rmax = num[Left];
        Tree[node].l = Tree[node].r = Left;
        return;
    }
    int mid = (Left + Right) >> 1;
    build(Left, mid, L(node));
    build(mid + 1, Right, R(node));
    update(node);
    return;
}
inline Node ask_max(int Left, int Right, int node){
    if(Left == Tree[node].l && Tree[node].r == Right)
        return Tree[node];
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(Right <= mid) return ask_max(Left, Right, L(node));
    else if(Left > mid) return ask_max(Left, Right, R(node));
    else return ask_max(Left, mid, L(node)) + ask_max(mid + 1, Right, R(node));
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, q, type;
    n = read();
    for(int i = 1; i <= n; i++) num[i] = read();
    build(1, n, 1);
    q = read();
    int x, y;
    while(q--){
        type = read();
        switch(type){
            case 0 :
                x = read(), y = read();
                change(x, y, 1);
                break;
            case 1 :
                x = read(), y = read();
                printf("%lld\n", ask_max(x, y, 1).Max);
                break;
        }
    }
    return 0;
}