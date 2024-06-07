#include<bits/stdc++.h>
/*
communities containing person i and j merged
print the size of the community to which person i belongs.
*/
using namespace std;
int *Fa = NULL, *Size = NULL;
inline int read(){
    int x=0, f=1;
    char ch=getchar();
    while(!isdigit(ch)) f = (ch =='-')?-1:1, ch = getchar();
    while(isdigit(ch)) x = (x<<3)+(x<<1)+ch-48, ch = getchar();
    return x*f;
}
inline int find(int x){
    return Fa[x] == x? x : Fa[x] = find(Fa[x]);
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    int N, Q;
    N = read(), Q = read();
    Fa = (int *)malloc(  N * sizeof(int));
    Size = (int *)malloc(  N * sizeof(int));
    for(int i = 0; i < N; i++) 
        Fa[i] = i ,  Size[i] = 1;
    char ch; 
    int x, y;
    while(Q--){
        ch=getchar();
        if(ch == 'Q'){
            x = read();
            printf("%d\n", Size[find(x)]);
        }else{  
            x=read(), y=read();
            int r1 = find(x), r2 = find(y);
            if(r1!=r2) Fa[r1] = r2, Size[r2]+=Size[r1];
        }
    }
    free(Fa), free(Size);
    return 0;
}