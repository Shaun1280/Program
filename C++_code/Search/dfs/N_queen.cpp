#include<bits/stdc++.h>
using namespace std;
int state[15], border_state;
int n, cnt;
char ch;
void dfs(int depth, int row, int obliqueL, int obliqueR){
    if(row == border_state){
        cnt++;
        return;
    }
    int cur_state = border_state &~ (state[depth] | row | obliqueL | obliqueR);
    int v;
    while(cur_state){
        v = cur_state & (~cur_state + 1);
        cur_state -= v;
        dfs(depth + 1, row + v, obliqueL + v >> 1, obliqueR + v << 1);
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            cin >> ch;
            if(ch == '.') state[i] |= (1 << j);
        }
    border_state = (1 << n) - 1;
    dfs(0, 0, 0, 0);      
    cout << cnt; 
    return 0;
}