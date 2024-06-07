#include<bits/stdc++.h>
const int MAXM = 2e3 + 3;
const int MAXN = 5e1 + 5;
const int Inf = 0x3f3f3f3f;
//P4822 [BJWC2012]冻结 k条路的权值能变为1/2
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int to, w, next;
    node(){}
    node(int _to, int _w, int _next){
        to = _to, w = _w, next = _next;
    }
}Edge[MAXM];
int tot, head[MAXN], inq[MAXN];
int dp[MAXN][MAXN], minDis = Inf;
inline void add_edge(int from, int to, int w){
    Edge[tot] = (node){to, w, head[from]};
    head[from] = tot++;
}
int n, m, k;
inline void spfa(){
    memset(dp, 0x3f, sizeof(dp));
    queue<int>q;
    q.push(1), inq[1] = true, dp[1][0] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to, w = Edge[i].w;
            for(int j = 0; j <= k; j++){
                if(dp[to][j] > dp[cur][j] + w){
                    dp[to][j] = dp[cur][j] + w;
                    if(!inq[to]) q.push(to), inq[to] = true;
                } 
                if(j < k && (dp[to][j + 1] > dp[cur][j] + w / 2) && dp[cur][j] != Inf){
                    dp[to][j + 1] = dp[cur][j] + w / 2;
                    if(!inq[to]) q.push(to), inq[to] = true;
                } 
            }   
        }
    }
    for(int i = 0; i <= k; i++) minDis = min(minDis, dp[n][i]);
    cout << minDis;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    while(m--){
        int u, v, w;
        u = read(), v = read(), w = read();
        add_edge(u, v, w), add_edge(v, u, w);
    }
    spfa();
    return 0;
}