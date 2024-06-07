#include<bits/stdc++.h>
const int maxn=1e5+5;
using namespace std;
int tot=0;
set<string>Str;
class word{
    public:
        stringstream ss;
        string s2;
        string s[maxn];
        char ch;
    public:
        inline void  get_string(){
            getline(cin,s2);
        }
        inline void Initiate(){
            ss.clear();
            ss.str(s2);
            while(ss>>s[tot]){
                Str.insert(s[tot++]);
            }
        }
        inline void testout_put(){
            for(int i=0;i<tot;i++)
            cout<<s[i]<<"*";
        }
};
int main(){
    word W;
    W.get_string();
    W.Initiate();
    W.testout_put();
    return 0;
}