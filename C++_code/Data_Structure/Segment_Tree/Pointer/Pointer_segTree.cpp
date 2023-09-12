#include<bits/stdc++.h>
//max_sequence point_change merge
//SP1716 GSS3 - Can you answer these queries III 
#define LL long long
const int MAXN = 5e4 + 4;
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
	Node * lson, *rson;
}Tree[MAXN << 1];
int num[MAXN], tot;
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
inline void update(Node * root){
    Node * lson = root->lson, *rson = root->rson;
    *root = *root->lson + *root->rson;
    root->lson = lson, root->rson = rson;
}
inline void change(int pos, int val, Node * root){
    if(root->l == pos && root->r == pos){
        root->Lmax = root->Rmax = val;
        root->sum = root->Max = val;
        return;
    }
    int mid= (root->l + root->r) >> 1;
    if(pos <= mid) change(pos, val, root->lson);
    else if(pos > mid) change(pos, val, root->rson);
    update(root);
    return;
}
inline void build(int Left, int Right, Node * root){
	root->l = Left, root->r = Right;
    if(Left == Right){
        root->Max = root->sum = root->Lmax = root->Rmax = num[Left];
        return;
    }
    root->lson = &Tree[++tot], root->rson = &Tree[++tot];
    int mid = (Left + Right) >> 1;
    build(Left, mid, root->lson);
    build(mid + 1, Right, root->rson);
    update(root);
    return;
}
inline Node ask_max(int Left, int Right, Node * root){
    if(Left == root->l && root->r == Right)
        return *root;
    int mid = (root->l + root->r) >> 1;
    if(Right <= mid) return ask_max(Left, Right, root->lson);
    else if(Left > mid) return ask_max(Left, Right, root->rson);
    else return ask_max(Left, mid, root->lson) + ask_max(mid + 1, Right, root->rson);
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    int n, q, type;
    n = read();
    for(int i = 1; i <= n; i++) num[i] = read();
    build(1, n, Tree);
    q = read();
    int x, y;
    while(q--){
        type = read();
        switch(type){
            case 0 :
                x = read(), y = read();
                change(x, y, Tree);
                break;
            case 1 :
                x = read(), y = read();
                printf("%lld\n", ask_max(x, y, Tree).Max);
                break;
        }
    }
    return 0;
}