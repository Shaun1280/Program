#include<bits/stdc++.h>
const int MAXN = 1e4 + 4;
//SP2916 GSS5 - Can you answer these queries V
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct Node{
    int l, r;
    int Max, sum;
    int maxPre, maxSuf;
}Tree[MAXN << 2];
#define L(x) (x << 1)
#define R(x) (x << 1 | 1)
inline Node operator + (Node Lson, Node Rson){
    Node tmp;
    tmp.l = Lson.l, tmp.r = Rson.r;
    tmp.sum = Lson.sum + Rson.sum;
    tmp.maxPre = max(Lson.maxPre, Lson.sum + Rson.maxPre);
    tmp.maxSuf = max(Rson.maxSuf, Rson.sum + Lson.maxSuf);
    tmp.Max = max(tmp.maxPre, tmp.maxSuf);
    tmp.Max = max(Lson.maxSuf + Rson.maxPre, max(Lson.Max, Rson.Max));
    return tmp;
}
inline void update(int node){
    Tree[node] = Tree[L(node)] + Tree[R(node)];
}
int num[MAXN];
inline void build(int L, int R, int node){
    if(L == R){
        Tree[node].sum = Tree[node].Max = num[L];
        Tree[node].maxPre = Tree[node].maxSuf = num[L];
        Tree[node].l = Tree[node].r = L;
        return;
    }
    int mid = (L + R) >> 1;
    build(L, mid, L(node));
    build(mid + 1, R, R(node));
    update(node);
}
inline Node query(int L, int R, int node){
    if(L == Tree[node].l && Tree[node].r == R){
        return Tree[node];
    }
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(R <= mid) return query(L, R, L(node));
    else if(L > mid) return query(L, R, R(node));
    else return query(L, mid, L(node)) + query(mid + 1, R, R(node));
}
int testCase;
int main(){
    testCase = read();
    while(testCase--){
        int n, m;
        n = read();
        for(int i = 1; i <= n; i++) num[i] = read();
        build(1, n, 1);
        m = read();
        int x1, x2, y1, y2;
        while(m--){
            x1 = read(), x2 = read(), y1 = read(), y2 = read();
            int ans;
            if(x2 > y1){
                ans = query(y1, x2, 1).Max;
                ans = max(ans, query(x1, y1, 1).maxSuf + query(y1, y2, 1).maxPre - num[y1]); 
                ans = max(ans, query(x1, x2, 1).maxSuf + query(x2, y2, 1).maxPre - num[x2]);
            }
            if(x2 == y1){
                ans = query(x1, x2, 1).maxSuf + query(y1, y2, 1).maxPre;
                ans -= num[x2];
            }
            if(x2 < y1){
                ans = query(x1, x2, 1).maxSuf + query(y1, y2, 1).maxPre + query(x2, y1, 1).sum;
                ans -= num[x2] + num[y1];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}