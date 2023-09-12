#include<bits/stdc++.h>
#define pii pair<int, int>
//https://www.luogu.com.cn/blog/user48611/p4366-code4-zui-duan-lu
//P4366 [Code+#4]最短路
const int MAXN = 1e5 + 5;
const int LOG = 17;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
vector<vector< pair<int, int> > >E;
int dis[MAXN], vis[MAXN], n, m, c;
priority_queue<pii, vector< pii >, greater< pii > >q;
inline void dijkstra(int s, int t){
    memset(dis, 0x3f, sizeof(dis));
    q.push(make_pair(dis[s] = 0, s));
    while(!q.empty()){
        int cur = q.top().second;
        q.pop();
        if(vis[cur]) continue;
        for(auto i : E[cur]){
            int to = i.first, w = i.second;
            if(dis[to] > dis[cur] + w){
                dis[to] = dis[cur] + w;
                q.push(make_pair(dis[to], to));
            }
        }
        vis[cur] = true;
    }
    cout << dis[t] << endl;
}
int main(){
    n = read(), m = read(), c = read();
    E.resize(n + 1);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        u = read(), v = read(), w = read();
        E[u].push_back(make_pair(v, w));
    }
    for(int u = 0; u <= n; u++)
        for(int i = 0; i <= LOG; i++){
            if((u ^ (1 << i)) > n) continue;
            E[u].push_back(make_pair(u ^ (1 << i), (1 << i) * c));
        }
    int s = read(), t = read();
    dijkstra(s, t);
    return 0;
}