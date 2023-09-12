#include<bits/stdc++.h>
typedef long long LL;
//https://www.luogu.com.cn/problem/P1593
//P1593 因子和
const int M = 9901;
using namespace std;
inline LL qpow(LL a, LL b){
    LL res = 1;
    while(b){
        if(b & 1) res = res * a % M;
        a = a % M * a % M;
        b >>= 1;
    }
    return res;
}
vector<pair<int, int> >w;
inline void divide(int a){
    for(int i = 2; i * i <= a; i++){
        if(a % i == 0){
            int cnt = 0;
            while(a % i == 0) cnt++, a /= i;
            w.push_back(make_pair(i, cnt));
        }    
    }
    if(a != 1) w.push_back(make_pair(a, 1));
}
inline LL get_sum(LL p, LL c){
    if(p == 0) return 0;
    if(c == 0) return 1;
    if(c & 1) return (1 + qpow(p, (c + 1) >> 1)) * get_sum(p, (c - 1) >> 1) % M;
    return ((1 + qpow(p, c >> 1)) * get_sum(p, (c >> 1) - 1) % M + qpow(p, c)) % M;
}
int main(){
    int a, b;
    cin >> a >> b;
    divide(a);
    int ans = 1;
    for(int i = 0; i < w.size(); i++){
        int p = w[i].first, c = w[i].second;
        ans = ans * get_sum(p, 1LL * b * c) % M;
    }
    cout << ans;
    return 0;
}