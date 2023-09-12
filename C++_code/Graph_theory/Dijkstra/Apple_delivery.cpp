#include<bits/stdc++.h>
const int MAXC = 2e5 + 5;
const int Inf = 2000000001;
//https://www.luogu.com.cn/problem/P3003
//P3003 [USACO10DEC]苹果交货Apple Delivery
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
vector<vector<pair<int, int> > >E;
int cowPath, P, s, t1, t2;
struct node{
    int pos, dis;
    inline bool friend operator < (const node &a, const node &b){
        return a.dis > b.dis;
    }
};
int dis[MAXC >> 1], vis[MAXC >> 1];
inline void dijkstra(int s){
    priority_queue<node, vector<node> >q;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= P; i++) dis[i] = Inf;
    q.push(node{s, dis[s] = 0});
    while(!q.empty()){
        int cur = q.top().pos;
        q.pop();
        if(vis[cur]) continue;
        for(auto i : E[cur]){
            int to = i.first, w = i.second;
            if(dis[to] > dis[cur] + w){
                dis[to] = dis[cur] + w;
                q.push(node{to, dis[to]});
            }
        }
        vis[cur] = true;
    }
}
int main(){
    cowPath = read(), P = read(), s = read(), t1 = read(), t2 = read();
    E.resize(P + 1);
    for(int i = 1; i <= cowPath; i++){
        int u, v, w;
        u = read(), v = read(), w = read();
        E[u].push_back(make_pair(v, w)), E[v].push_back(make_pair(u, w));
    }
    int sum = 0;
    dijkstra(s);
    if(dis[t1] > dis[t2]){
        sum += dis[t2], s = t2;
        dijkstra(s);
        sum += dis[t1];
        cout << sum;
        return 0;
    }
    sum += dis[t1], s = t1;
    dijkstra(s);
    sum += dis[t2];
    cout << sum;
    return 0;
}