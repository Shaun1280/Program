#include<bits/stdc++.h>
const int maxn=1e4+4;
using namespace std;
int T,n;
int dp[maxn];
vector<int>chocolate;
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48, ch=getchar();
    return x*f;
}
inline void get_dp(){
    for(int i=5;i<=10001;i++)
        dp[i] =i/5+dp[i%5];
}
int main(){
    T=read();
    dp[0]=0, dp[1]=1, dp[2]=1, dp[3]=2, dp[4]=2;
    get_dp();
    while(T--){
        cin>>n;
        chocolate.clear();
        int cnt1(0),cnt2(0),cnt3(0);
        for(int i=0,tmp;i<n;i++) tmp=read(), chocolate.push_back(tmp);
        int min_val=*min_element(chocolate.begin(),chocolate.end());
        for(auto i:chocolate){
            cnt1+=dp[i-min_val];
            cnt2+=dp[i-(min_val-1)];
            cnt3+=dp[i-(min_val-2)];
        }
        cout<<min(min(cnt1,cnt2),cnt3)<<"\n";
    }
    return 0;
}