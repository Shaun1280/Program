#include<bits/stdc++.h>
#define Inf 0x7fffffff
using namespace std;
int n,tmp,cnt1(0),cnt2(0);
vector<int>Array, cp_Array;
bool have_p1=false,have_start=false, have_end=false;
int Start=1, End=Array.size(), pos1(0),pos2(0);
inline bool Judge_swap(vector<int>&A){
    for(int i=1;i<=n;i++){
        if(A[i]>A[i-1]&&A[i]>A[i+1]&&!have_p1) pos1=i, have_p1=true;
        if(A[i]<A[i-1]&&A[i]<A[i+1]) pos2=i;
    }        
    if(pos1>0&&pos2>0){ swap(A[pos1],A[pos2]); return true;}
    return false;
}
inline bool judge_reverse(vector<int>&A){
    for(int i=1;i<=n;i++){
        if(A[i]<A[i-1]&&!have_start)
            Start=i-1, have_start=true;
        if(A[i]>A[i-1]&&have_start){ 
            if(++cnt2==2) return false;
            End=i-1, have_start=false;
        }
    }
    return true;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n;
    Array.push_back(-Inf);
    for(int i=0;i<n;i++) cin>>tmp, Array.push_back(tmp);
    Array.push_back(Inf);
    cp_Array.assign(Array.begin(),Array.end());
    bool Swap=Judge_swap(cp_Array);
    bool Reverse=judge_reverse(Array);
    if(Swap) for(int i=1;i<=n;i++) if(cp_Array[i]<cp_Array[i-1]) Swap=false;
    if(Swap){cout<<"yes\nswap "<<pos1<<" "<<pos2; return 0;}
    if(Reverse) sort(Array.begin()+Start,Array.begin()+End+1);
    for(int i=1;i<=n;i++) if(Array[i]<Array[i-1]) Reverse=false;
    if(Reverse){cout<<"yes\nreverse "<<Start<<" "<<End; return 0;}
    cout<<"no";
    return 0;
}