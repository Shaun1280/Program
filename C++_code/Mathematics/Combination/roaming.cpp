#include<bits/stdc++.h>
//AT 156E - Roaming
//https://www.luogu.com.cn/problem/AT5312
//calculating nCm with precaculations in O(1) time
constexpr int M = 1e9 + 7;
constexpr int MAXN = 2e5 + 5;
#define pii pair<int, int>
typedef long long LL;
typedef unsigned long long uLL;
using namespace std;
LL n, k, fac[MAXN], rev_fac[MAXN];
inline LL qpow(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}
inline LL getC(LL m, LL n) {
    return rev_fac[n - m + 1] * qpow(fac[m], M - 2) % M;
}
int main(){
    LL res = 0;
    cin >> n >> k;
	fac[0] = rev_fac[n + 1] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % M;
    for (int i = n; i >= 1; i--) rev_fac[i] = rev_fac[i + 1] * i % M;
    for (LL i = 0; i <= min(n - 1, k); i++) {
        res = (res + getC(i, n) * getC(n - i - 1, n - 1) % M * qpow(n, M - 2) % M) % M;
    }
    cout << res << endl;
	return 0;
}