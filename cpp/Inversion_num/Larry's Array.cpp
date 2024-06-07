#include<bits/stdc++.h>
const int maxn=1e3+1;
using namespace std;
int T,n,sum;
int inversion_num[maxn];
int num[maxn];
inline void get_inversion(int Index){
    for(int i=0;i<Index;i++)
        if(num[i]>num[Index]) inversion_num[Index]++;
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n;
        sum=0;
        memset(inversion_num, 0, sizeof(inversion_num));
        for(int i=0; i<n; i++) cin >> num[i], get_inversion(i);
        for(int i=0; i<n; i++) sum += inversion_num[i];
        if(sum%2==0) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;  
    }
    return 0;
}