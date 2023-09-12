#include<bits/stdc++.h>
/*P3084 [USACO13OPEN]照片Photo*/
const int MAXM = 1e6 + 6;
const int MAXN = 2e5 + 5;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f; 
}
struct node{
    int to, w, next;
}Edge[MAXM];
int head[MAXN], cnt;
inline void add_edge(int from, int to, int w){
    Edge[cnt] = (node){to, w, head[from]};
    head[from] = cnt++;
}
int inq[MAXN], sum[MAXN];
inline bool spfa(){
    double start = clock() / (double)CLOCKS_PER_SEC;
    memset(sum, 0x3f, sizeof(sum));
    deque<int>q;
    q.push_front(0), sum[0] = 0, inq[0] = true;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front(), inq[cur] = false;
        double now = clock() / (double)CLOCKS_PER_SEC;
        if(now - start > 0.7) return false;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to, w = Edge[i].w;
            if(sum[to] > sum[cur] + w){
                sum[to] = sum[cur] + w;
                if(!inq[to]){
                    if(q.empty() || sum[to] < sum[q.front()]) q.push_front(to);
                        else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
    return true;
}
int n, m;
int main(){
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    int u, v;
    /*0 <= sum[i] - sum[i - 1] <= 1*/
    for(int i = 1; i <= n; i++)
        add_edge(i - 1, i, 1), add_edge(i, i - 1, 0);
    while(m--){
        u = read(), v = read();
        /*1<=sum[u] - sum[v - 1]<=1*/
        add_edge(u - 1, v, 1), add_edge(v, u - 1, -1);
    }
    cout << (spfa() ? sum[n] : -1);
    return 0;
}