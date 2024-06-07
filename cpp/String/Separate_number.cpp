#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL T,min_val;
int L,init_size; 
bool leading_zero, Find;
string s,tmp;
inline void search_next(int p, LL num, LL min_num,int cnt){
    LL N; 
    int Size;
    if(p==L&&cnt>1) 
        Find=true,  min_val=min_num; 
    tmp=s.substr(p,(init_size+p>L?L-p:init_size));
    Size=tmp.size();
    if(tmp[0]=='0') return;
    stringstream ss;
    ss<<tmp, ss>>N;
    while(N!=0){
        if(N==num+1ll){
            search_next(p+Size,N,min_num,cnt+1);
            break;
        }
        N/=10ll, Size--;
    }
    return;
}
inline void Init(){
    L=s.size(), leading_zero=false, Find=false;
    if(s[0]=='0'||L==1) leading_zero=true;
}
int main(){
    cin>>T;
    cin.ignore();
    while(T--){
        s.clear();
        getline(cin,s);
        Init();
        if(leading_zero){ 
            cout<<"NO"<<endl; 
            continue; 
        }
        for(int i=0;i<=(L>>1|1);i++){
            LL num;
            tmp=s.substr(0, i+1);
            init_size=i+2;//8+1=9, 9+1=10
            stringstream ss;
            ss<<tmp, ss>>num;
            search_next(i+1,num,num,1);
        }
        if(Find) cout<<"YES "<<min_val<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}