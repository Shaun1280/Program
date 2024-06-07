#include<bits/stdc++.h>
//P2471 [SCOI2007]降雨量
const int MAXN  = 5e4 + 4;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
struct node{
    int year, rainFall;
    inline friend bool operator < (const node &a, const node &b){
        return a.year < b.year;
    }
};
int n, m;
vector<node>Y;
struct segTree{
    int l, r, Max;
}Tree[MAXN << 2];
#define L(x) (x << 1) 
#define R(x) (x << 1 | 1)
inline void update(int node){
    Tree[node].Max = max(Tree[L(node)].Max, Tree[R(node)].Max);
}
inline void build(int Left, int Right, int node){
    Tree[node].l = Left, Tree[node].r = Right;
    if(Left == Right){
        Tree[node].Max = Y[Left].rainFall;
        return;
    }
    int mid = (Left + Right) >> 1;
    build(Left, mid, L(node));
    build(mid + 1, Right, R(node));
    update(node);
}
inline int ask_max(int Left, int Right, int node){
    if(Tree[node].l == Left && Tree[node].r == Right)
        return Tree[node].Max;
    int mid = (Tree[node].l + Tree[node].r) >> 1;
    if(Right <= mid) return ask_max(Left, Right, L(node));
    else if(Left > mid) return ask_max(Left, Right, R(node));
    else return max(ask_max(Left, mid, L(node)), ask_max(mid + 1, Right, R(node)));
}
#define TRUE printf("true\n")
#define FALSE printf("false\n")
#define MAYBE printf("maybe\n")
int main(){
    n = read();
    Y.resize(n + 1);
    for(int i = 1; i <= n; i++)
        Y[i].year = read(), Y[i].rainFall = read();
    build(1, n, 1);
    m = read();
    while(m--){
        int y, x;// query X年是自Y年以来降雨量最多的
        node tmpY, tmpX;
        y = read(), x = read();
        tmpY.year = y, tmpX.year = x;
        int yId = lower_bound(Y.begin() + 1, Y.end(), tmpY) - Y.begin();
        int xId = lower_bound(Y.begin() + 1, Y.end(), tmpX) - Y.begin();
        bool knowY = true, knowX = true;
        if(Y[yId].year != y) knowY = false;
        if(Y[xId].year != x) knowX = false;
        if(x == y) TRUE;
        else{
            if(knowX && knowY){
                if(yId < xId - 1){
                    int Max = ask_max(yId + 1, xId - 1, 1);
                    if(Y[xId].rainFall > Max && Y[xId].rainFall <= Y[yId].rainFall && x - y == xId - yId)
                        TRUE;
                    else if(Y[xId].rainFall <= Max || Y[xId].rainFall > Y[yId].rainFall)
                        FALSE;
                    else MAYBE;
                } else{ //两年相邻
                    if(Y[xId].rainFall <= Y[yId].rainFall && x - y == xId - yId)
                        TRUE;
                    else if(Y[xId].rainFall > Y[yId].rainFall)
                        FALSE;
                    else MAYBE;
                }
            } else if(knowX && !knowY){ //Y年份降雨未知
                if(yId <= xId - 1 && Y[xId].rainFall <= ask_max(yId, xId - 1, 1))
                    FALSE; 
                else MAYBE;
            } else if(!knowX && knowY){ //X年份降雨未知
                xId--;
                if(yId < xId && Y[yId].rainFall <= ask_max(yId + 1, xId, 1))
                    FALSE;
                else MAYBE;
            }  else MAYBE;
        }
    }
    //cout << "Okay" << endl;
    return 0;
}