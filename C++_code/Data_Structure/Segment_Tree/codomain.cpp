#include<bits/stdc++.h>
/*P5459 [BJOI2016]回转寿司
第一次这样写，由题目可以推出公式   sum(r)-R<=sum(l-1)<=sum(r)-L  //[l,r]是一个满足条件的区间
只要计算当前前缀和之前满足条件的前缀和个数，累加起来就是答案。
我们想到利用线段树，每次让对应的前缀和加1，然后统计一下在满足条件下的前缀和总个数，可这个值最大1e10，不可能开出四倍这个空间，
但是N最大10w，不同的数并不会出现那么多，我们利用一种动态的思想，当用到某个数的时候在给他分配节点，这样用不到的数的空间就被节约下来了。
这样的话节点就要保存左右儿子的id值才能准确的访问左右儿子，其他和线段树差不多。
*/
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
    int Lson, Rson;
}Tree[MAXN * LOG];
LL sum[MAXN], ans;
int root, tot;
#define L(node) Tree[node].Lson
#define R(node) Tree[node].Rson
inline void update(int node){
    Tree[node].cnt = Tree[L(node)].cnt + Tree[R(node)].cnt;
}
inline void build(int &node, LL L, LL R, LL val){
    if(!node) node = ++tot;
    if(L == R){
        Tree[node].cnt++;
        return;
    }
    LL mid = L + R >> 1;
    if(val <= mid) build(L(node), L, mid, val);
        else build(R(node), mid + 1, R, val);
    update(node);
}
inline LL ask_cnt(int node, LL L, LL R, LL qL, LL qR){
    if(qL == L && R == qR) return Tree[node].cnt;
    LL mid = L + R >> 1, tmp = 0;
    if(qL <= mid) tmp += ask_cnt(L(node), L, mid, qL, qR);
    if(qR > mid) tmp += ask_cnt(R(node), mid + 1, R, qL, qR);
    return tmp;
}
int main(){
    int n, l, r;
    n = read(), l = read(), r = read();
    for(int i = 1, tmp; i <= n; i++)
        tmp = read(), sum[i] = sum[i - 1] + tmp;
    build(root, -Inf, Inf, sum[0]);
    for(int i = 1; i <= n; i++){
        ans += ask_cnt(root, -Inf, Inf, sum[i] - r, sum[i] - l);
        build(root, -Inf, Inf, sum[i]);
    }
    cout << ans;
    return 0;
}