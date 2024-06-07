#include<bits/stdc++.h>
/*Sherlock and the Valid String*/
/*valid:
    characters appear the same number of times
    can remove just 1 character at 1 index in the string
    vector< pair< char,int> > vec(map.begin(), map.end());
*/
const int MAXN=1e5+5;
using namespace std;//NO //YES
map<char,int>cnt;
int total_cnt=1;
inline bool cmp(const pair< char,int> &a,pair <char,int> &b){
    return a.second < b.second;
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    string s;
    getline(cin,s);
    for(auto c : s) cnt[c]++; // count times that a character appears
    vector< pair< char,int> > vec(cnt.begin(), cnt.end());
    sort(vec.begin(),vec.end(),cmp);
    for(int i=1; i<vec.size();i++)
        if(vec[i].second!=vec[i-1].second)
            if((++total_cnt)>2){
                printf("NO");
                return 0;
            }
    bool Judge1=true, Judge2=true;   
    for(int i=1; i<vec.size()-1;i++) 
        if(vec[i].second!=vec[i-1].second) Judge1=false;
    for(int i=2; i<vec.size();i++) 
        if(vec[i].second!=vec[i-1].second) Judge2=false;  
    if(vec[vec.size()-1].second!=vec[vec.size()-2].second 
    && vec[vec.size()-1].second-1!=vec[vec.size()-2].second) 
        Judge1=false;
    if(vec[1].second!=vec[0].second && vec[0].second>1) 
        Judge2=false; 
    if(Judge1||Judge2) printf("YES");
    else printf("NO");
    return 0;
}