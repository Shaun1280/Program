#include<bits/stdc++.h>
const int maxn=1e5+5;
using namespace std;
int r_q,c_q,n,k,r_ob[maxn],c_ob[maxn];
int cnt(0);
inline void find_row(){
    int dis_up=n-r_q;
    int dis_down=r_q-1;
    for(int i=1;i<=k;i++){
        if(c_ob[i]==c_q&&r_ob[i]>r_q) dis_up=min(dis_up, r_ob[i]-r_q-1);
        if(c_ob[i]==c_q&&r_ob[i]<r_q) dis_down=min(dis_down,r_q-r_ob[i]-1);
    }
    cnt+=dis_up+dis_down;
    return;
}
inline void find_column(){
    int dis_right=n-c_q;
    int dis_left=c_q-1;
    for(int i=1;i<=k;i++){
        if(r_ob[i]==r_q&&c_ob[i]>c_q) dis_right=min(dis_right, c_ob[i]-c_q-1);
        if(r_ob[i]==r_q&&c_ob[i]<c_q) dis_left=min(dis_left,c_q-c_ob[i]-1);
    }
    cnt+=dis_right+dis_left;
    return;
}
inline void find_r_q1(){
    int dis_up=min(n-c_q,n-r_q);
    int dis_down=min(r_q-1,c_q-1);
    for(int i=1;i<=k;i++){
        if(c_ob[i]-c_q==r_ob[i]-r_q&&r_ob[i]>r_q) dis_up=min(dis_up, r_ob[i]-r_q-1);
        if(c_ob[i]-c_q==r_ob[i]-r_q&&r_ob[i]<r_q) dis_down=min(dis_down,r_q-r_ob[i]-1);
    }
    cnt+=dis_up+dis_down;
    return;
}
inline void find_r_q2(){
    int dis_up=min(n-r_q,c_q-1);
    int dis_down=min(r_q-1,n-c_q);
    for(int i=1;i<=k;i++){
        if(c_ob[i]-c_q==(-1)*(r_ob[i]-r_q)&&r_ob[i]>r_q) dis_up=min(dis_up, r_ob[i]-r_q-1);
        if(c_ob[i]-c_q==(-1)*(r_ob[i]-r_q)&&r_ob[i]<r_q) dis_down=min(dis_down,r_q-r_ob[i]-1);
    }
    cnt+=dis_up+dis_down;
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n>>k>>r_q>>c_q;
    for(int i=1;i<=k;i++)  cin>>r_ob[i]>>c_ob[i];
    find_row(),find_column(),find_r_q1(),find_r_q2();
    cout<<cnt;
    return 0;
}