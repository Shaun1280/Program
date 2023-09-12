/*
#include<iostream>
#include<map>
using namespace std;

int main()
{
   int n; cin >> n;
   int save=n;
   int min=n+1, x, index=1;
   map<int, int> m;
   while(n--)
   {
       cin >> x;
       if (m[x] && ((index-m[x])<min))
            min=index-m[x];
       m[x]=index++;
   }
   if (min!=(save+1)) cout << min;
   else cout << -1;
}
*/
#include<bits/stdc++.h>
const int maxn=1e5+5;
using namespace std;
struct A{int val,pos;};
int n,cnt(0),P[maxn],min_val=maxn;
A tmp;
bool Start[maxn];
vector<A>Array;
inline bool cmp1(const A &v1, const A &v2){
    return v1.val<v2.val;
}
inline bool cmp2(const A &v1,const A &v2){
    return v1.pos<v2.pos;
}
inline void find_min(){
    for(int i=1;i<n;i++) 
        if(!Start[i]) min_val=min(min_val,Array[i].pos-Array[i-1].pos);    
}
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n;
    memset(P,0,sizeof(P));
    memset(Start,false,sizeof(Start));
    for(int i=0;i<n;i++) 
        cin>>tmp.val,tmp.pos=i, Array.push_back(tmp);
    sort(Array.begin(),Array.end(),cmp1);
    for(int i=1;i<n;i++) 
        if(Array[i].val!=Array[i-1].val) P[++cnt]=i,Start[i]=true;
    for(int i=0;i<cnt;i++) 
        sort(Array.begin()+P[i],Array.begin()+P[i+1],cmp2);
    sort(Array.begin()+P[cnt],Array.end(),cmp2);
    find_min();
    cout<<(min_val==maxn?-1:min_val);
    return 0;
}