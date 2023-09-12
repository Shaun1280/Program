#include<bits/stdc++.h>
#define LL long long
using namespace std;
int q,n;
LL horizontal[101];
LL vertical[101];
LL num[101][101];
int main(){
    std::ios::sync_with_stdio(false);
    cin>>q;
    while(q--){
        int cnt(0);
        memset(vertical,0,sizeof(vertical));
        memset(horizontal,0,sizeof(horizontal));
        cin>>n;
        for(int container=0;container<n;container++)
            for(int Type=0;Type<n;Type++)
                cin>>num[container][Type];
        for(int container=0;container<n;container++)
            for(int Type=0;Type<n;Type++)
                horizontal[container]+=num[container][Type];
        for(int Type=0;Type<n;Type++)
            for(int container=0;container<n;container++)
                vertical[Type]+=num[container][Type];
        for(int container=0;container<n;container++)
            for(int Type=0;Type<n;Type++)
                if(horizontal[container]==vertical[Type]){
                    cnt++;
                    vertical[Type]=0;
                    break;
                }
        cout<<( cnt==n ? "Possible":"Impossible" )<<endl;
    }
    return 0;
}