#include<bits/stdc++.h>
#define LL long long 
const int MAXN = 1e5 + 6;
/**https://www.luogu.com.cn/problem/P1666
 * https://www.luogu.com.cn/blog/TangLongbin/solution-p1666
 * trie + dp
 * **/
using namespace std;
struct node{
    int to, next;
    node(){}
    node(int _to, int _next){
        to = _to, next = _next;
    }
}Edge[MAXN];
int head[MAXN], edgeCnt;
inline void add(int from, int to){
    Edge[edgeCnt] = (node){to, head[from]};
    head[from] = edgeCnt++;
}
int trie[MAXN][26], End[MAXN], tot = 1;
inline void insert(string str){
    int p = 1;
    for(int i = 0; i < str.size(); i++){
        int ch = str[i] - 'a';
        if(trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    End[p] = true;
}
inline void rebuild(int cur, int fa){
    if(End[cur]) add(fa, cur), fa = cur;
    for(int i = 0 ; i < 26 ; i++)
        if(trie[cur][i]) rebuild(trie[cur][i], fa);
}
LL dp[MAXN][2];
void dfs(int cur){
    dp[cur][0] = dp[cur][1] = 1LL;
    for(int i = head[cur]; ~i; i = Edge[i].next){
        int to = Edge[i].to;
        dfs(to);
        dp[cur][0] *= dp[to][0] + dp[to][1];
    }
}
int n;
vector<string>vec;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n, vec.resize(n);
    memset(head, -1, sizeof(head));
    for(int i = 0; i < n; i++) cin >> vec[i], insert(vec[i]);
    for(int i = 0; i < 26; i++)
        if(trie[1][i]) rebuild(trie[1][i], 1);
    dfs(1);
    cout << dp[1][0];
    return 0;
}