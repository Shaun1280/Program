#include<bits/stdc++.h>
using namespace std;
int main(){
    std::ios::sync_with_stdio(false);
    int T, Size;
    cin>>T;
    while(T--){
        string s, ascii_s;
        string reverse_s,ascii_reverse_s;
        cin>>s, reverse_s=s, Size=s.size();
        ascii_reverse_s.clear(), ascii_s.clear();
        reverse(reverse_s.begin(),reverse_s.end());
        for(int i=1,tmp;i<Size;i++) 
            tmp=abs(s[i]-s[i-1]), ascii_s+=to_string(tmp);
        for(int i=1,tmp;i<Size;i++) 
            tmp=abs(reverse_s[i]-reverse_s[i-1]), ascii_reverse_s+=to_string(tmp);
        cout<<(ascii_reverse_s==ascii_s ? "Funny" : "Not Funny")<<endl;
    }
    return 0;
}