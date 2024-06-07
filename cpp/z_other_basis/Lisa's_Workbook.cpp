#include<bits/stdc++.h>
const  int maxn=1e5+5;
using namespace std;
struct P{
    int Begin,End;
};
P tmpp;
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    std::ios::sync_with_stdio(false);
    int n,k,tmp,Ch,cnt(0);
    vector<int>chapter;
    vector<P>Page;
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>tmp, chapter.push_back(tmp);
    for(int i=0;i<n;i++){
        tmpp.Begin=1, tmpp.End=min(chapter[i],k),Ch=chapter[i];
        if(chapter[i]<=k){
            Page.push_back(tmpp);
            continue;
        } 
        Page.push_back(tmpp);
        while(true){
            chapter[i]-=k;
            if(chapter[i]<=k){
                tmpp.Begin+=k,tmpp.End=Ch;
                Page.push_back(tmpp);
                break;
            }
            tmpp.Begin+=k,tmpp.End+=k, Page.push_back(tmpp);
        } 
    }
    for(int i=0;i<Page.size();i++)
        cout<<"Page"<<i<<" "<<Page[i].Begin<<" "<<Page[i].End<<endl;
    for(int i=0;i<Page.size();i++)
        if(Page[i].Begin<=i+1&&Page[i].End>=i+1) cnt++;
    cout<<cnt<<endl;
    return 0;
} 