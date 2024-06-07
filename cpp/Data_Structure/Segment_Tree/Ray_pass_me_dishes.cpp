#include<bits/stdc++.h>
#define LL long long
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
const int MAXN = 5e5 + 5;
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
    int L, R;
    int pre_r/*最大前缀结束位置*/, suf_l/*最大后缀开始位置*/;
    LL Lmax, Rmax, Max, sum;
}Tree[MAXN << 2];
int num[MAXN];
inline Node operator + (Node Lson, Node Rson){
    Node tmp;
    tmp.l = Lson.l, tmp.r = Rson.r;
    tmp.sum = Lson.sum + Rson.sum;
    tmp.Lmax = Lson.Lmax, tmp.Rmax = Rson.Rmax;
    tmp.pre_r = Lson.pre_r, tmp.suf_l = Rson.suf_l;
    /*********左区间全部加右区间前缀**************/
    tmp.Max = Lson.sum + Rson.Lmax;
    tmp.L = Lson.L, tmp.R = Rson.pre_r;
    /*************只取左区间********************/
    if(tmp.Max < Lson.Max || (tmp.Max == Lson.Max && tmp.L == Lson.L)){
        tmp.Max = Lson.Max;
        tmp.L = Lson.L, tmp.R = Lson.R;
    }
    /*************左边后缀加右边前缀**************/
    if(tmp.Max < Lson.Rmax + Rson.Lmax || (tmp.Max == Lson.Rmax + Rson.Lmax && tmp.L > Lson.suf_l)){
        tmp.Max = Lson.Rmax + Rson.Lmax;
        tmp.L = Lson.suf_l;
        tmp.R = Rson.pre_r;
    }
    /*************左边后缀加右边sum**************/
    if(tmp.Max < Lson.Rmax + Rson.sum || (tmp.Max == Lson.Rmax + Rson.sum && tmp.L > Lson.suf_l)){
        tmp.Max = Lson.Rmax + Rson.sum;
        tmp.L = Lson.suf_l;
        tmp.R = Rson.r;
    }
    /*************右边max**************/
    if(tmp.Max < Rson.Max || (tmp.Max == Rson.Max && tmp.L > Rson.suf_l)){
        tmp.Max = Rson.Max;
        tmp.L = Rson.L;
        tmp.R = Rson.R;
    }
    if(Lson.sum + Rson.Lmax > tmp.Lmax){
        tmp.Lmax = Lson.sum + Rson.Lmax;
        tmp.pre_r = Rson.pre_r;
    }
    if(Lson.Rmax + Rson.sum >= tmp.Rmax){
        tmp.Rmax = Lson.Rmax + Rson.sum;
        tmp.suf_l = Lson.suf_l;
    }
    //区间左端某一段最大子段和 区间右端某一段最大子段和 左区间最靠右的一段+右区间最靠左的一段的最大值
    return tmp;
}
inline void update(int node){
    Tree[node] = Tree[L(node)] + Tree[R(node)];
    return;
}
inline void build(int Left, int Right, int node){
    if(Left == Right){
        Tree[node].Max = Tree[node].sum = Tree[node].Lmax = Tree[node].Rmax = num[Left];
        Tree[node].l = Tree[node].r = Left;
        Tree[node].L = Tree[node].R = Left;
        Tree[node].pre_r = Tree[node].suf_l = Left;
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
    int n, q, tot = 0;
    while(scanf("%d%d", &n, &q) == 2){
        for(int i = 1; i <= n; i++) num[i] = read();
        build(1, n, 1);
        int x, y;
        printf("Case %d:\n", ++tot);
        while(q--){
            x = read(), y = read();
            Node tmp = ask_max(x, y, 1);
            printf("%d %d\n", tmp.L, tmp.R);
        }
    }
    return 0;
}