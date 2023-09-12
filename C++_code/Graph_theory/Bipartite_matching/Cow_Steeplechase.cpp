#include<bits/stdc++.h>
//P3033 [USACO11NOV]牛的障碍Cow Steeplechase
//https://www.luogu.com.cn/problem/P3033
const int MAXN = 1e3;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int x1, y1;
    int x2, y2;
};
vector<node>horizon; //y1 = y2
vector<node>vertical;
bool E[MAXN][MAXN];
bool used[MAXN];
int match[MAXN];
int n;
bool dfs(int x){
    for(int i = 0; i < vertical.size(); i++){
        if(E[x][i] && !used[i]){
            used[i] = true;
            if(match[i] == -1 || dfs(match[i])){
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    //freopen("test.in","r", stdin);
    n = read();
    for(int i = 1; i <= n; i++){
        node tmp;
        tmp.x1 = read(), tmp.y1 = read(), tmp.x2 = read(), tmp.y2 = read();
        if(tmp.y1 == tmp.y2){
            if(tmp.x1 > tmp.x2) swap(tmp.x1, tmp.x2);
            horizon.push_back(tmp);
            continue;
        }
        if(tmp.x1 == tmp.x2) {
            if(tmp.y1 > tmp.y2) swap(tmp.y1, tmp.y2);
            vertical.push_back(tmp);
        }
    }
    for(int i = 0; i < horizon.size(); i++)
        for(int j = 0; j < vertical.size(); j++){
            node line1 = horizon[i], line2 = vertical[j];
            if(line1.x1 <= line2.x1 && line1.x2 >= line2.x1 && line1.y1 >= line2.y1 && line1.y1 <= line2.y2) 
                E[i][j] = true;
        }
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < horizon.size(); i++){
        memset(used, 0, sizeof(used));
        if(dfs(i)) cnt++;
    }
    cout << n - cnt << endl;
    return 0;
}