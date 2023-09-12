#include<bits/stdc++.h>
using namespace std;//0 based_index
int n,tmpc,range,cnt(0);
vector<int>city;
int main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin>>n>>range, range--;
    for(int i=0;i<n;i++) cin>>tmpc, city.push_back(tmpc);
    int Index=0;
    while(Index<city.size()){
        bool found=false;
        // do backward search from the furthest possible to current
        for(int j=min(Index+range,n-1);j>=max(0,Index-range);j--){
                if(city[j]){
                    cnt++;
                    // put plant here and 
                    // calculate the new beginning
                    Index=j+range+1;//search next
                    found=true;
                    break;
                }
        }
        if(!found) {cnt=-1;break;}
    }
    cout<<cnt;
    return 0;
}