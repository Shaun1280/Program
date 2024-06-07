#include<bits/stdc++.h>
//https://ac.nowcoder.com/acm/contest/1010/B
using namespace std;
const int MAXN = 100005 << 5;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int trie[MAXN][2], cnt = 1;
inline void insert(int num){
    int p = 1;
    for(int i = 31; i >= 0; i--){
        int k = (num >> i) & 1;
        if(!trie[p][k]) trie[p][k] = ++cnt;
        p = trie[p][k];
    }
}
int ans = 0;
inline void search(int num){
    int w = 0, p = 1; //从根节点开始查找
    for(int i = 31; i >= 0; i--){
        int k = (num >> i) & 1;
        if(trie[p][k ^ 1]){ //优先选择当前位不同，则异或值为1
            w = (w << 1) + (k ^ 1);
            p = trie[p][k ^ 1];
        } else { //只能选择相同，异或值为0
            w = (w << 1) + k;
            p = trie[p][k];
        }
    }
    ans = max(ans, w ^ num);
}
int n;
int main(){
    n = read();
    for(int i = 0, tmp = 0; i < n; i++){
        tmp = read();
        insert(tmp); //插入trie树
        if(i >= 1) search(tmp); 
    }
    cout << ans;
    return 0;
}