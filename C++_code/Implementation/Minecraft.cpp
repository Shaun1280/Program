#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXSIZE 800
#define BLOCKHEIGHT 6
#define BLOCKCOLUMN 7
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
int N, M;   
char block[BLOCKHEIGHT + 1][BLOCKCOLUMN +1] = { //每个block6行7列
    "+---+..",
    "|\\   \\.",
    "| +---+",
    "+ |   |",
    ".\\|   |",
    "..+---+",
};
int height[51][51];
int vis[MAXSIZE][MAXSIZE];
char map[MAXSIZE + 100][MAXSIZE + 100];
int maxHeight;
inline static void draw_block(int x, int y){
    for(int i = x; i < x + BLOCKHEIGHT; i++){
        for(int j = y; j < y + BLOCKCOLUMN; j++){
            if(vis[i][j] && block[i - x][j - y] == '.') continue;
            map[i][j] = block[i - x][j - y];
            vis[i][j] = 1;
        }
    }   
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    /*
    3 4
    2 1 1 4 
    3 1 1 1
    1 1 2 3
    */
    scanf("%d%d", &M, &N); //M行 N列
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++){
            scanf("%d", &height[i][j]);
            maxHeight = max(maxHeight, height[i][j]);
        } 
    for(int i = 0; i <= MAXSIZE; i++)
        for(int j = 0; j <= MAXSIZE; j++)
            map[i][j] = '.';
    printf("aaaaaa");
    int startI = MAXSIZE - 2 * M - 3, startJ = 4 * N - 4;
    // for(int h = 1; h <= maxHeight; h++){
    //     for(int i = 0; i < M; i++){
    //         for(int j = N - 1; j >= 0; j--){
    //             startJ -= 4;
    //             if(height[i][j] < h) continue;
    //             draw_block(startI, startJ + 4);
    //         }
    //         startI += 2, startJ = 4 * N - 4 + (i + 1) * 2;
    //     }
    //     startI = MAXSIZE - 2 * M - 3 - h * 3, startJ = 4 * N - 4;
    // }
    // int printr = -1, printc = -1;
    // for(int i = 1; i <= MAXSIZE; i++){
    //     for(int j = 0; j <= MAXSIZE; j++)
    //         if(map[i][j] != '.'){printr = i; break;}
    //     if(printr >=0 ) break;
    // }
    // for(int j = MAXSIZE; j >= 0; j--){
    //      for(int i = 1; i <= MAXSIZE; i++)
    //         if(map[i][j] != '.'){printc = j; break;}
    //     if(printc >=0 ) break;
    // } 
    // for(int i = 0; i <= MAXSIZE; i++){
    //     for(int j = 0; j <= MAXSIZE; j++)
    //         putchar(map[i][j]);
    //     putchar('\n');
    // }
    //printf("%d %d\n", printr, printc);
    return 0;
/*
............+---+......
............|\   \.....
............| +---+....
............+ |   |....
............|\|   |....
..+---+.....| +---+....
+-|\   \....+ |   |....
|\| +---+...|\| +---+..
| + |   |...| +-|\   \.
+ |\|   |---+ | | +---+
|\| +---+\  +---+ |   |
| + |   |-+-|\   \|   |
+ |\|   |  \| +---+---+
.\| +---+---+ |   |   |
..+ |\   \   \|   |   |
...\| +---+---+---+---+
....+ |   |   |   |   |
.....\|   |   |   |   |
......+---+---+---+---+
*/
}