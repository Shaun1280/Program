#include<bits/stdc++.h>
#define LL long long
using namespace std;
int T;
LL n,a,b;
int main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin>>T;
    vector<LL>num;
    while(T--){
        cin>>n>>a>>b;
        n--;
        num.clear();
        LL Min=ceil((1.0*n)/2);
        for(LL i=Min;i<=n;i++){
            num.push_back(i*a+(n-i)*b);
            num.push_back(i*b+(n-i)*a);
        }     
        sort(num.begin(),num.end());
        for(int i=1;i<num.size();i++)
            if(num[i]==num[i-1]) num.erase(num.begin()+i),i--;
        for(int i=0;i<num.size();i++)
            cout<<num[i]<<" ";
            cout<<endl;
    }
    return 0;
}