#include<bits/stdc++.h>
typedef unsigned long long LL;
//1e6不同单词数
const LL P = 131;
using namespace std;
vector<LL>H;
inline LL Hash(string s){
    LL sum = 0;
    for(int i = 0; i < s.size(); i++){
        sum = (sum * P + s[i]);
    }
    return sum;
}
int n;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        H.push_back(Hash(s));
    }
    sort(H.begin(), H.end());
    int cnt = 1;
    for(int i = 1; i < n; i++)
        if(H[i] != H[i - 1]) cnt++;
    cout << cnt;
    return 0;
}