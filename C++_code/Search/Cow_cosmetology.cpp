#include<bits/stdc++.h>
/*P2124 奶牛美容
BFS && floy min distance
*/
const int MAXN = 50;
using namespace std;
int row, column, cnt, ans = 0x7fffffff;
int block[50][50], vis[50][50];
int dis_block_point[4][50][50];
int dis_block[4][4];
int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};
struct node{ int r, c; };
inline void Get_block(int r, int c){ //BFS
    queue< node >q;
    q.push((node){r, c});
    block[r][c] = cnt;
    while(!q.empty()){
        int cur_r = q.front().r, cur_c = q.front().c;
        q.pop();
        if(vis[cur_r][cur_c]) continue;
        for(int i = 0; i < 4; i++){
            int next_r = cur_r + dr[i];
            int next_c = cur_c + dc[i];
            if(vis[next_r][next_c] || !block[next_r][next_c]) continue;
            if(next_r < 0 || next_r >= row) continue;
            if(next_c < 0 || next_c >= column) continue;
            q.push((node){next_r, next_c});
            block[next_r][next_c] = cnt;
        }
        vis[cur_r][cur_c] = true;
    }
}
inline void Get_dis(int B, int r, int c){
     for(int i = 0 ;i < row; i++)
        for(int j = 0 ; j < column; j++)
            dis_block_point[B][i][j] = min(dis_block_point[B][i][j], abs(r - i)+abs(c - j)); 
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> row >> column;
    getchar();
    for(int i = 0 ;i < row; i++){
        for(int j = 0 ; j < column; j++)
            block[i][j] = (getchar()=='.') ? 0 : 1;
        getchar(); //get data
    }
    for(int i = 0 ;i < row; i++)
        for(int j = 0 ; j < column; j++)
            if(block[i][j]&&!vis[i][j]) 
                cnt++, Get_block(i,j);
    // BFS get blockcnt fomr 1 to 3
    memset(dis_block_point, 0x7f, sizeof(dis_block_point));
    memset(dis_block, 0x7f, sizeof(dis_block));
    for(int i = 0 ;i < row; i++)
        for(int j = 0 ; j < column; j++)
            if(block[i][j]) Get_dis(block[i][j], i, j);
    /*get min_dis between block[i] and everypoint*/  
    for(int i = 0 ;i < row; i++)
        for(int j = 0 ; j < column; j++){
            int P = block[i][j];
            dis_block[P][1] = min(dis_block[P][1], dis_block_point[1][i][j]);
            dis_block[P][2] = min(dis_block[P][2], dis_block_point[2][i][j]);
            dis_block[P][3] = min(dis_block[P][3], dis_block_point[3][i][j]); 
            dis_block[1][P] = dis_block[P][1];
            dis_block[2][P] = dis_block[P][2];
            dis_block[3][P] = dis_block[P][3];
        }
    /*get min distance between any two blocks*/
    ans = min(dis_block[1][2] + dis_block[1][3], min(dis_block[2][1] + dis_block[2][3], dis_block[3][1] + dis_block[3][2]));
    for(int i = 0 ;i < row; i++)
        for(int j = 0 ; j < column; j++)
            ans = min(ans, dis_block_point[1][i][j] + dis_block_point[2][i][j] + dis_block_point[3][i][j]);
    cout<< ans -2;
    return 0;
}