/*Implementation Strange Counter*/
#include<bits/stdc++.h>
#define LL long long
struct S{ 
    LL Time, value;
    inline bool operator < (const S &a) const{
        return Time < a.Time;
    }
};
using namespace std;
S tmp;
vector<S>Table;
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    LL T;
    cin>>T;
    tmp.Time=1ll,tmp.value=3ll;
    Table.push_back(tmp);
    while(true){
        tmp.Time=Table.back().Time+Table.back().value;
        tmp.value=2ll*Table.back().value;
        if(tmp.Time>T) break;
        Table.push_back(tmp);
    }
    tmp.Time=T;
    int Index=lower_bound(Table.begin(),Table.end(),tmp)-Table.begin();
    int End=Table.size()-1;
    Index=min(Index, End);
    cout<<(Table[Index].value-(T-Table[Index].Time));
    return 0;
}