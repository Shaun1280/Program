#include<bits/stdc++.h>
const int SIZE = 9;
using namespace std;
map<int, bool> horizontal[SIZE];
map<int, bool> vertical[SIZE];
map<int, bool> block[SIZE]; //行 列 块 的元素是否被访问过 
int m[SIZE][SIZE], tmp;

inline void print(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            printf("%d ", m[i][j]);
        putchar('\n');
    }
    exit(0);
}

void dfs(int curx, int cury){
    if(curx >= SIZE || cury >= SIZE) return;
    if(m[curx][cury]){
        if(curx == SIZE - 1 && cury == SIZE - 1) print();
            else if(cury == SIZE - 1) dfs(curx + 1, 0);
        else dfs(curx, cury + 1);
    } else{
        for(int i = 1; i <= 9; i++){    
            int id = curx / 3 * 3 + cury / 3;
            if(horizontal[curx][i] || vertical[cury][i] || block[id][i]) 
                continue;
            m[curx][cury] = i;
            horizontal[curx][i] = vertical[cury][i] = block[id][i] = true;
            if(curx == SIZE - 1 && cury == SIZE - 1) print();
                else if(cury == SIZE - 1) dfs(curx + 1, 0);
            else dfs(curx, cury + 1);  
            m[curx][cury] = false; //回溯
            horizontal[curx][i] = vertical[cury][i] = block[id][i] = false;  
        }
    }
}

int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            cin >> m[i][j], tmp = m[i][j]; 
            if(!tmp) continue;
            horizontal[i][tmp] = true;
            vertical[j][tmp] = true;
            int id = i / 3 * 3 + j / 3;
            //three rows id + 3, three columns id + 1 
            block[id][tmp] = true;
        }
    dfs(0, 0);        
    return 0;
}