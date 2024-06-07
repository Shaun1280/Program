#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/cf76d-plus-and-xor
typedef unsigned long long LL;
using namespace std;
LL a, b;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> a >> b;
    LL dif = a - b;
    if(dif < 0 || (dif & 1)){
        cout << -1;
        return 0;
    }
    cout << (dif >> 1) << " " << (a - (dif >> 1));
    return 0;
}