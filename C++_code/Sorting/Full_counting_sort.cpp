#include<bits/stdc++.h>
const int Maxn=1e2+1;
using namespace std;
struct S{
    int cnt;
    vector<string>s;
}node[Maxn];
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    int n, val, max_val(0);
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0; i<n; i++){
        string S;
        cin>>val>>S;
        max_val=max(max_val,val);
        node[val].cnt++;
        node[val].s.push_back( i <= ( n-2 >> 1 ) ? "-" : S);
    }
    for(int i=0; i<=max_val; i++)
        for(int j=0; j<node[i].cnt; j++)
            cout<<node[i].s[j]<<" ";
    return 0;
}