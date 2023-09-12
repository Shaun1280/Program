#include<bits/stdc++.h>
const int Max_val=1e2+1;
using namespace std;
int n,cnt[Max_val], max_val;
vector<int>num;
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out","w", stdout);
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0, tmp; i<n; i++) 
        cin>>tmp, num.push_back(tmp), max_val=max(max_val, tmp);
    for(int i=0; i<n; i++) cnt[num[i]]++; 
    for(int i=0; i<=max_val; i++) 
        if(cnt[i])
            for(int j=0; j<cnt[i]; j++)   
                cout<<i<<" ";
    return 0;
}