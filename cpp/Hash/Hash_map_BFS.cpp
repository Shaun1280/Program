#include<bits/stdc++.h>
/*P2730 Magic Squares*/
using namespace std;
struct node{
    string present_string;
    string path;
};
string Start="12345678", End, tmp;
unordered_map<string, bool>m(100005);
inline string A (string s){
    for(int i = 0; i < 4; ++i) swap(s[i], s[7 - i]);
    return s;
}
inline string B (string s){
    swap(s[0], s[3]), swap(s[4], s[7]), swap(s[1], s[3]);
    swap(s[4], s[5]), swap(s[2], s[3]), swap(s[5], s[6]);
    return s;
}
inline string C (string s){
    swap(s[1], s[6]), swap(s[2], s[6]), swap(s[5], s[6]);
    return s;
}
inline void BFS(){
    queue <node> q;
    q.push( (node){Start, " "} );
    while(!q.empty()){
        string s=q.front().present_string, path=q.front().path;
        q.pop();
        if(s==End){
            cout<<path.size()-1<<endl;
            for(int i=1; i<path.size(); i++) cout<<path[i];
            return ;
        }
        string a=A(s), b=B(s), c=C(s);
        if(!m[a]) m[a]=true, q.push( (node){a, path+"A"});
        if(!m[b]) m[b]=true, q.push( (node){b, path+"B"});
        if(!m[c]) m[c]=true, q.push( (node){c, path+"C"});
    }
}
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    for(int i=0; i<8; i++) cin>>tmp, End+=tmp;
    BFS();
    return 0;
}