#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-48, ch=getchar();
    return x*f;
}
int T, n;
struct node{ int Index,val;};
vector<node>vec, ordered_vec;
node tmp;
inline bool cmp1(const node &a, const node &b){
    if(a.val==b.val) return a.Index < b.Index;
    return a.val<b.val;
}
inline bool cmp2(const node &a, const node &b){
    return a.Index < b.Index;
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    T=read();
    while(T--){
        vec.clear(), ordered_vec.clear();
        n=read();
        for(int i=0; i<n; i++)
            tmp.val=read(), tmp.Index=i, vec.push_back(tmp);
        sort(vec.begin(), vec.end(), cmp1);
        ordered_vec.push_back(vec[0]);
        for(int i=1; i<n; i++)
            if(vec[i].val!=vec[i-1].val) ordered_vec.push_back(vec[i]);
        sort(ordered_vec.begin(),ordered_vec.end(),cmp2);
        for(int i=0; i<ordered_vec.size();i++) 
            printf("%d ", ordered_vec[i].val);
        putchar('\n');
    }
    return 0;
}