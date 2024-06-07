#include<bits/stdc++.h>
typedef long long LL;
const int MAXN = 3e6 + 6;
using namespace std;
LL inv[MAXN];
LL n, mod;
int main(){
    //std::ios::sync_with_stdio(false);
    cin >> n >> mod;
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    for(int i = 1; i <= n; i++)
        printf("%lld\n", inv[i]);
    return 0;
}