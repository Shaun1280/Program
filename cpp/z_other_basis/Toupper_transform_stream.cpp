#include<bits/stdc++.h>
const int maxn=1e4+4;
using namespace std;
int tot=0;
class words{
    public:
        stringstream ss;
        string s2;
        string s[maxn];
    public:
        inline void get_string(){
            getline(cin,s2);
        }
        inline void Initiate(){
            ss.clear();
            ss.str(s2);
            while(ss>>s[tot]){
            	transform(s[tot].begin(),s[tot].end(),s[tot].begin(),::toupper);
                tot++;
            }
        }
         inline void testout_put(){
            for(int i=0;i<tot;i++)
            cout<<s[i]<<"*";
        }
};
int main(){
    words W;
    W.get_string();
    W.Initiate();
    W.testout_put();
    return 0;
}
