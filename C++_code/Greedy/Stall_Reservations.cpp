#include<bits/stdc++.h>
const int MAXN = 5e4 + 4;
//P2859 [USACO06FEB]摊位预订Stall Reservations
//https://www.luogu.com.cn/blog/user48611/p2859-usaco06feb-tan-wei-yu-ding-stall-reservations
//https://www.luogu.com.cn/problem/P2859
#define pii pair<int, int>
using namespace std;
priority_queue<pii, vector< pii >, greater< pii > >q;
struct node{
    int id, st, ed;
    inline friend bool operator < (const node &a, const node &b){
        return a.st < b.st;
    }
};
vector<node>cow;
int n, stall[MAXN], tot;
int main(){
    scanf("%d", &n);
    cow.resize(n);
    for(int i = 0; i < n; i++) scanf("%d%d", &cow[i].st, &cow[i].ed), cow[i].id = i;
    sort(cow.begin(), cow.end());
    q.push(make_pair(cow[0].ed, ++tot));
    stall[cow[0].id] = tot;
    for(int i = 1; i < n; i++){
        if(cow[i].st <= q.top().first){
            q.push(make_pair(cow[i].ed, ++tot));
            stall[cow[i].id] = tot;
            continue;
        }
        stall[cow[i].id] = q.top().second;
        q.pop();
        q.push(make_pair(cow[i].ed, stall[cow[i].id]));
    }
    printf("%d\n", tot);
    for(int i = 0; i < n; i++) printf("%d\n", stall[i]);
    return 0;
}