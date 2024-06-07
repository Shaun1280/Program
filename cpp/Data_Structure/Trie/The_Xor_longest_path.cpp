#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXP = MAXN << 5;
/*
https://www.luogu.com.cn/problem/P4551
1.先进行一次深度优先遍历，求出Xor[x] = Xor[fa[x]] xor Weight

从x到y路径上的所有边权异或后的值为Xor[x] ^ Xor[y]

(同一条边异或两次结果不变, x到根和y到根的重叠部分抵消掉)

于是问题化为求max(Xor[i] ^ Xor[j]), i, j ∈[1,n], 可以trie树解决The xor largest pair
*/
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f; 
}
struct node{
    int to, next, w;
    node(){}
    node(int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXN << 1];
int head[MAXN], tot;
inline void add_edge(int from, int to, int w){
    Edge[tot] = node(to, w, head[from]);
    head[from] = tot++;
}
int trie[MAXP][2], cnt = 1, Xor[MAXN];
void dfs(int cur, int fa){
    for(int i = head[cur]; ~i; i = Edge[i].next){
        int to = Edge[i].to, w = Edge[i].w;
        if(to == fa) continue;
        Xor[to] = Xor[cur] ^ w; 
        dfs(to, cur);
    }
}
int ans;
inline void insert(int num){
    int p = 1;
    for(int i = 31; i >= 0; i--){
        int k = (num >> i) & 1;
        if(!trie[p][k]) trie[p][k] = ++cnt;
        p = trie[p][k];
    }
}
inline void search(int num){
    int w = 0, p = 1;
    for(int i = 31; i >= 0; i--){
        int k = (num >> i) & 1;
        if(trie[p][k ^ 1]){
            w = (w << 1) + (k ^ 1);
            p = trie[p][k ^ 1];
        } else {
            w = (w << 1) + k;
            p = trie[p][k];
        }
    }
    ans = max(ans, w ^ num);
}
int n;
int main(){
    n = read();
    memset(head, -1, sizeof(head));
    for(int i = 0; i < n - 1; i++){
        int u, v, w;
        u = read(), v = read(), w = read();
        add_edge(u, v, w), add_edge(v, u, w);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++){
        insert(Xor[i]);
        if(i == 1) continue;
        search(Xor[i]);
    }
    cout << ans;
    return 0;
}