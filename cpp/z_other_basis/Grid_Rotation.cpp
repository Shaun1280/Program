/*Matrix Layer Rotation Hard*/
/*
*convet into a line and push_back it into a dequeue 
 change pos
 .front(), pop_front();
*/
#include<bits/stdc++.h>
const int Maxn=3e2+1;
using namespace std;
static int m,n;
inline int read(){
    int x=0, f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-48, ch=getchar();
    return x*f;
}
inline void rotate_this_Layer(int r1, int r2, int c1, int c2, int Map[][Maxn], int copy_Map[][Maxn], int rotation){
    int Deltar=r2-r1+1, Deltac=c2-c1+1;
    for(int row=r1+1; row<=r2; row++){
        if( rotation > r2-row+Deltar-1+Deltac-1+Deltac-1)
            copy_Map[r1+rotation-(r2-row+Deltar-1+Deltac-1+Deltac-1)][c1]=Map[row][c1]; 
        else if( rotation > r2-row+Deltar+Deltac-2)
            copy_Map[r1][c2-(rotation-(r2-row+Deltar+Deltac-2))]=Map[row][c1]; 
        else if( rotation > r2-row+Deltac-1)
            copy_Map[r2-(rotation-(r2-row+Deltac-1))][c2]=Map[row][c1];
        else if( rotation > r2-row)
            copy_Map[r2][c1+rotation-(r2-row)]=Map[row][c1];
        else copy_Map[row+rotation][c1]=Map[row][c1];
    } 
    //2
    for(int column=c1+1; column<=c2; column++)
        if(rotation > c2-column+Deltar-1+Deltac-1+Deltar-1)
            copy_Map[r2][c1+rotation-(c2-column+Deltar-1+Deltac-1+Deltar-1)]=Map[r2][column];
        else if( rotation > c2-column+Deltar+Deltac-2)//shu
            copy_Map[r1+(rotation-(c2-column+Deltar+Deltac-2))][c1]=Map[r2][column];
        else if( rotation > c2-column+Deltar-1)
            copy_Map[r1][c2-(rotation-(c2-column+Deltar-1))]=Map[r2][column];
        else if( rotation > c2-column)
            copy_Map[r2-(rotation-(c2-column))][c2]=Map[r2][column];
        else copy_Map[r2][column+rotation]=Map[r2][column];
    //3
    for(int row=r2-1; row>=r1;row--)
        if( rotation > row-r1+Deltar-1+Deltac-1+Deltac-1)//heng
            copy_Map[r2-(rotation-(row-r1+Deltar-1+Deltac-1+Deltac-1))][c2]=Map[row][c2];
        else if( rotation > row-r1+Deltar+Deltac-2)//heng
            copy_Map[r2][c1+rotation-(row-r1+Deltar+Deltac-2)]=Map[row][c2];  
        else if( rotation > row-r1+Deltac-1)//shu
            copy_Map[r1+(rotation-(row-r1+Deltac-1))][c1]=Map[row][c2];
        else if( rotation > row-r1)//heng
            copy_Map[r1][c2-(rotation-(row-r1))]=Map[row][c2]; 
        else copy_Map[row-rotation][c2]=Map[row][c2];//shu
    //4
    for(int column=c2-1; column>=c1; column--)
        if( rotation > column-c1+Deltar+Deltac-2+Deltar-1)//shu
            copy_Map[r1][c2-(rotation-(column-c1+Deltar+Deltac-2+Deltar-1))]=Map[r1][column];
        else if( rotation > column-c1+Deltar+Deltac-2)//shu
            copy_Map[r2-(rotation-(column-c1+Deltar+Deltac-2))][c2]=Map[r1][column]; 
        else if( rotation > column-c1+Deltar-1)
            copy_Map[r2][c1+rotation-(column-c1+Deltar-1)]=Map[r1][column];
        else if( rotation > column-c1)
            copy_Map[r1+(rotation-(column-c1))][c1]=Map[r1][column];
        else copy_Map[r1][column-rotation]=Map[r1][column];
}
inline void Layer_rotate(int r1, int c1, int Map[][Maxn], int copy_Map[][Maxn], int rotation){
    int r2=m-r1-1, c2=n-c1-1, copy_rotation=rotation;
    int Deltar=r2-r1+1, Deltac=c2-c1+1;
    if( rotation >= ((Deltar+Deltac<<1)-4) ) rotation %= ((Deltar+Deltac<<1)-4);
    rotate_this_Layer(r1, r2, c1, c2, Map, copy_Map, rotation);
    if( ( r1+1!=r2 ) && ( c1+1!=c2) ) 
        Layer_rotate(r1+1, c1+1, Map, copy_Map, copy_rotation);     
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    static int Map[Maxn][Maxn], copy_Map[Maxn][Maxn];
    int rotation;
    m=read(),n=read(), rotation=read();
    memset(copy_Map,0,sizeof(copy_Map));
    for(int i=0; i<m; i++) for(int j=0; j<n; j++) Map[i][j]=read();
    Layer_rotate(0, 0, Map, copy_Map, rotation);
     for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            cout<<copy_Map[i][j]<<" ";
        cout<<endl;
     }
    return 0;
}