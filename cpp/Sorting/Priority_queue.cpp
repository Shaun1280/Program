/*big sorting*/
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int digits; string s;
    bool operator < (const Node &N) const{
        if(N.digits < digits) return true;
        if(N.digits == digits) return N.s<s;
        return false;
    }
};
int main(){
    std::ios::sync_with_stdio(false);
    priority_queue< Node ,vector<Node> >q;
    int n;
    cin>>n;
    cin.ignore();
    for(int i=0;i<n;i++){
        string S;
        cin>>S;
        q.push( (Node) {S.size(),S} );
    }
    for(int i=0;i<n;i++) cout<<q.top().s<<endl, q.pop();
    return 0;
}