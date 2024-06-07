#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/p5459-bjoi2016-hui-zhuai-shou-si
//P5459 [BJOI2016]回转寿司
const int MAXN = 1e5 + 5;
const int LOG = 34;
typedef long long LL;
const LL Inf = 1e10;
using namespace std;
inline LL read(){
    LL x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct segTree{
    int cnt;
    LL l, r;
    int Lson, Rson;
}Tree[MAXN * LOG];
LL sum[MAXN], ans;
int root, tot;
#define Lnode Tree[node].Lson
#define Rnode Tree[node].Rson
inline void update(int node){
    Tree[node].cnt = Tree[Lnode].cnt + Tree[Rnode].cnt;
}
inline void build(int &node, LL L, LL R, LL val){
    if(!node) {
        node = ++tot;
        Tree[node].l = L, Tree[node].r = R;
    }
    if(L == R){
        Tree[node].cnt++;
        return;
    }
    LL mid = L + R >> 1;
    if(val <= mid) build(Lnode, L, mid, val);
        else build(Rnode, mid + 1, R, val);
    update(node);
}
inline LL ask_cnt(int node, LL L, LL R){
    if(!node) return 0;
    if(L <= Tree[node].l && Tree[node].r <= R) 
        return Tree[node].cnt;
    LL mid = Tree[node].l + Tree[node].r >> 1, tmp = 0;
    if(L <= mid) tmp += ask_cnt(Lnode, L, R);
    if(R > mid) tmp += ask_cnt(Rnode, L, R);
    return tmp;
}
int main(){
    int n, l, r;
    n = read(), l = read(), r = read();
    for(int i = 1, tmp; i <= n; i++)
        tmp = read(), sum[i] = sum[i - 1] + tmp;
    build(root, -Inf, Inf, sum[0]);
    for(int i = 1; i <= n; i++){
        ans += ask_cnt(root, sum[i] - r, sum[i] - l);
        build(root, -Inf, Inf, sum[i]);
    }
    cout << ans;
    return 0;
}