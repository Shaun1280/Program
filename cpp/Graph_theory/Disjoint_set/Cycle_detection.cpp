#include<bits/stdc++.h>
const int MAXN = 1e5 + 5;
//https://www.luogu.com.cn/problem/CF859E
//https://codeforces.com/blog/entry/54572
const long long M = 1e9 + 7;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int fa[MAXN << 1], sz[MAXN << 1], selfLoop[MAXN << 1], cycle[MAXN << 1];
inline int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int n;
int main(){
    n = read();
    for(int i = 1; i <= n << 1; i++) fa[i] = i, sz[i] = 1;
    for(int i = 1; i <= n; i++){
        int u = read(), v = read();
        if(u == v) selfLoop[find(u)] = 1;//自环
        int r1 = find(u), r2 = find(v);
        if(r1 != r2){
            fa[r1] = r2;
            sz[r2] += sz[r1], sz[r1] = 0;
            selfLoop[r2] |= selfLoop[r1];
            continue;
        }   
        cycle[r1] = true; //已处于同一个集合，出现环
    }
    long long ans = 1;
    for(int i = 1; i <= n << 1; i++){
        if(find(i) == i) {//根节点
            if(selfLoop[i]) continue;
            else if(cycle[i]) ans = ans * 2 % M;
            else ans = ans * sz[i] % M;
        }
    }
    cout << ans;
    return 0;
}