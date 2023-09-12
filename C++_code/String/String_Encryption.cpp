#include<bits/stdc++.h>
using namespace std;
string s; stringstream ss;
double L;
int row(0),column;
inline void Init(){
    getline(cin,s);
    for(int i=0;i<s.size();i++) if(s[i]!=' ') ss<<s[i];
    ss>>s;
    L=s.size();
    column=ceil(sqrt(L));
}
inline void Split(){
    string Encryption[100], S;
    for(int i=0;i<(int)L;i+=column)
        if(i+column>L) Encryption[row++]=s.substr(i,L-i);
        else Encryption[row++]=s.substr(i,column);
    //for(int i=0;i<row;i++) cout<<Encryption[i]<<endl;
    for(int j=0;j<column;j++){
        for(int i=0;i<row;i++)
            if('a'<=Encryption[i][j]&&Encryption[i][j]<='z')cout<<Encryption[i][j];  
        cout<<" ";
    }     
}
int main(){
    std::ios::sync_with_stdio(false);
    Init();
    Split();
    return 0;
}