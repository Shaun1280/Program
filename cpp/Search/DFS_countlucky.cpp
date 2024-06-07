#include<bits/stdc++.h>
const int maxn=1e3+1;
using namespace std;
bool visited[maxn][maxn], Lucky;
string Map[maxn];
int dc[4]={1,0,-1,0}, dr[4]={0,1,0,-1};
int T, R, C, L;
inline void Search(int row,int column,int cnt){
    visited[row][column]=true;
    if(Map[row][column]=='*'){if(cnt==L) Lucky=true; return;}
    int now_r,now_c, now_cnt(0);
    for(int i=0;i<4;i++){
        now_r=row+dr[i], now_c=column+dc[i];
        if(now_r>=R||now_r<0||now_c>=C||now_c<0) continue;
        if(!visited[now_r][now_c]&&Map[now_r][now_c]!='X') 
            now_cnt++;
    }
    for(int i=0;i<4;i++){
        now_r=row+dr[i], now_c=column+dc[i];
        if(now_r>=R||now_r<0||now_c>=C||now_c<0) continue;
        if(!visited[now_r][now_c]&&Map[now_r][now_c]!='X')
            Search(now_r,now_c, now_cnt>1 ? cnt+1:cnt);
    }
    return;
}
inline void Init(){
    memset(visited,false,sizeof(visited));
    for(int i=0;i<R;i++) Map[i].clear(),getline(cin,Map[i]);
    cin>>L, Lucky=false;
    for(int i=0;i<R;i++) for(int j=0;j<C;j++)
        if(Map[i][j]=='M') Search(i,j,0);
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>R>>C;
        cin.ignore();
        Init();  
        cout<<(Lucky?"Impressed\n":"Oops!\n");
    }
    return 0;
}