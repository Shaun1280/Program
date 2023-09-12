#include<bits/stdc++.h>
//P2052 [NOI2011]道路修建
const int MAXN = 1e6 + 6;
using namespace std;
typedef long long LL;
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
int n;
int head[MAXN], tot, cnt[MAXN];
inline void add_edge(int from, int to, int w){
    Edge[tot] = node(to, w, head[from]);
    head[from] = tot++;
}
LL sum;
void dfs(int cur, int fa){
    cnt[cur] = 1;
    for(int i = head[cur]; ~i; i = Edge[i].next){
        int to = Edge[i].to;
        if(to == fa) continue;
        dfs(to, cur);
        sum += 1LL * abs(cnt[to] - (n - cnt[to])) * Edge[i].w;
        cnt[cur] += cnt[to];
    }
}
int main(){
     freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    n = read();
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n - 1; i++){
        int u, v, w; 
        cin >> u >> v >> w;
        add_edge(u, v, w), add_edge(v, u, w);
    }
    dfs(1, 0);
    cout << sum << endl;
    return 0;
}