#include<bits/stdc++.h>
//P1196 [NOI2002]银河英雄传说
const int MAXN  = 3e4 + 4;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int T;
char type;
int x, y;
int Fa[MAXN], front[MAXN], Size[MAXN];
inline int find(int x){
    if(Fa[x] == x) return x;
    int f = find(Fa[x]);
    front[x] += front[Fa[x]];
    return Fa[x] = f;
}
int main(){
    T = read();
    for(int i = 1; i <= 30000; i++)
        Fa[i] = i, front[i] = 0, Size[i] = 1;
    while(T--){
        cin >> type >> x >> y;
        int r1 = find(x), r2 = find(y);
        switch (type){
            case 'M'://x接在y的尾部
                front[r1] += Size[r2];
                Fa[r1] = r2;
                Size[r2] += Size[r1]; 
                Size[r1] = 0; //r1不再为队首 size = 0
                break;
            case 'C':
                if(r1 != r2) printf("-1\n");
                    else printf("%d\n", abs(front[x] - front[y]) - 1);
                break;
        }
    }
    return 0;
}