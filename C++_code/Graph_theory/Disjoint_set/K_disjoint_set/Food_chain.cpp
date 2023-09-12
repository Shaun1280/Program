#include<bits/stdc++.h>
//P2024 [NOI2001]食物链
const int MAXN = 5e4 + 4;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
/*
    x元素所在集合中所有∈[1，n]的元素都是x元素的同类
    x+n元素所在集合中所有∈[1，n]的元素都是x元素的猎物
    x+n元素所在的集合中所有∈[1，n]的元素都是x+2n元素的天敌
    x+2n元素所在集合中所有∈[1，n]的元素都是x元素的天敌
    A吃B, B吃C, C吃A, 但A不会吃C
    由题意若x，y是同类，则分别合并x和y，x+n和y+n，x+2n和y+2n
    表示xy是同类，x的天敌是y的天敌，x的猎物是y的猎物
    若x吃y，则合并x和y+n，x+n和y+2n，x+2n和y
    表示x吃y，x的猎物吃y的猎物，x的猎物的猎物吃y的猎物的猎物   
*/
int n, K, fake, Fa[MAXN << 2];
inline int find(int x){
    return Fa[x] == x ? x : Fa[x] = find(Fa[x]);
}
inline void Union(int a, int b){
    int r1 = find(a), r2 = find(b);
    if(r1 != r2) Fa[r2] = r1;
}
int main(){
    n = read(), K = read();
    for(int i = 1; i <= n * 3; i++) Fa[i] = i;
    while(K--){
        int type, x, y;
        type = read(), x = read(), y = read();
        if(x > n || y > n) {fake++; continue;}
        switch (type)
        {
        case 1://x 与 y为同类
            if(find(x + n) == find(y) || find(x + 2 * n) == find(y)) fake++;
            /*x的猎物和y在一个集合, x的天敌和y在一个集合 false*/
            else Union(x, y), Union(x + n, y + n), Union(x + 2 * n, y + 2 * n);
            break;
        case 2://x 吃 y
            if(x == y || find(x) == find(y) || find(y + n) == find(x)) fake++;
            /*x与y在一个集合 y的猎物和x在一个集合 false*/
            else Union(x + n, y), Union(x, y + 2 * n), Union(x + 2 * n, y + n);
            /*x的猎物和y在一个集合，y的天敌和x在一个集合，x的天敌和y的天敌在一个集合*/
            break;
            //  x<-y<-z
        }
    }
    cout << fake << endl;
    return 0;
}