#include<bits/stdc++.h>
const int MAXN = 2e2 + 1;
const int MAXM = 3e3 + 3;
typedef long long LL;
using namespace std;
int n, m, p/*kinds of monster*/, k/*num_of_blacksmith*/;
int sVillage[1 << 14];
int dp[MAXN][1 << 14]; //到达点i状态为j的最小时间
struct E{
    int to, t, state, next;
    E(){}
    E(int _to, int _t, int _state, int _next){
        to = _to, t = _t, state = _state, next = _next;
    }
}Edge[MAXM << 1];
int head[MAXN], cnt, vis[MAXN][1 << 14];
inline void add_edge(int from, int to, int t, int state){
    Edge[cnt] = (E){to, t, state, head[from]};
    head[from] = cnt++;
}
struct node{
    int p, t, state;
    inline friend bool operator < (const node &a, const node &b){
        return a.t > b.t;
    }
};
inline int dijkstra(){
    priority_queue<node, vector<node>>q;
    memset(dp, 0x3f, sizeof(dp)), dp[1][sVillage[1]] = 0;
    q.push((node){1, 0, sVillage[1]});
    while(!q.empty()){
        int cur = q.top().p;
        int curTime = q.top().t;
        int curState = q.top().state;
        q.pop();
        if(cur == n) return curTime;
        if(vis[cur][curState]) continue;
        for(int i = head[cur]; ~i; i = Edge[i].next){
            int to = Edge[i].to, t = Edge[i].t, eState = Edge[i].state;
            if((curState | eState) != curState) continue; /*非包含关系 不能通过*/
            int nextState = (curState | sVillage[to]); //下一个点的状态
            if(dp[to][nextState] > curTime + t){
                dp[to][nextState] = curTime + t;
                q.push((node){to, dp[to][nextState], nextState});
            }
        }
        vis[cur][curState] = true;
    }
    return -1;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n >> m >> p >> k;
    memset(head, -1, sizeof(head));
    for(int i = 1, w, p; i <= k; i++){
        cin >> w >> p;
        for(int j = 1, tmp; j <= p; j++){
            cin >> tmp;
            sVillage[w] |= 1 << (tmp - 1);
        }
    }
    for(int i = 1, u, v, t, s; i <= m; i++){
        cin >> u >> v >> t >> s;
        int sMonster = 0;
        for(int j = 1, tmp; j <= s; j++)
            cin >> tmp, sMonster |= 1 << (tmp - 1);
        add_edge(u, v, t, sMonster), add_edge(v, u, t, sMonster);
    }
    cout << dijkstra();
    return 0;
}