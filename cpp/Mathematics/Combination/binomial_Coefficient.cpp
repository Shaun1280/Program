#include<bits/stdc++.h>
typedef long long LL;
const int MAXN = 1e3 + 3;
const int Mod = 1e4 + 7;
using namespace std;
int C[MAXN][MAXN];
inline int qpow(LL a, LL b, LL res){ //a^b
    while(b){
        if(b & 1) res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}
LL a, b, k, n, m, ans;
inline void Init(){
    for(int i = 0; i <= k; i++) C[i][0] = 1;
    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= k; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> a >> b >> k >> n >> m;
    Init();
    ans = C[k][m] * qpow(b, m, 1) % Mod * qpow(a, n, 1) % Mod;
    cout << ans << endl;
    return 0;
}