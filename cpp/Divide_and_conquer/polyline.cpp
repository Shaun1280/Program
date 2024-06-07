#include<bits/stdc++.h>
typedef long long LL;
//https://www.luogu.com.cn/problem/CF171H
//https://www.luogu.com.cn/blog/user48611/cf171h-a-polyline
using namespace std;
pair<LL, LL> calc(int n, LL m){
    if(n == 0) return make_pair(0, 0);
    LL len = 1LL << (n - 1), cnt = 1LL << (2 * n - 2);
    pair<LL, LL> pos = calc(n - 1, m % cnt);
    LL x = pos.first, y = pos.second;
    LL z = m / cnt;
    if(z == 0) return make_pair(y, x);
    if(z == 1) return make_pair(x, y + len);
    if(z == 2) return make_pair(x + len, y + len);
    return make_pair(2 * len - y - 1, len - x - 1);
}
int main(){
    LL n, m;
    cin >> n >> m;
    pair<LL, LL> pos = calc(n, m);
    LL x = pos.first, y = pos.second;
    cout << x << " " << y << endl;
    return 0;
}