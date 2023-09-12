#include<bits/stdc++.h>
typedef long long LL;
//P5431 【模板】乘法逆元2
//https://www.luogu.com.cn/problem/P5431
const int MAXN = 5e6 + 6;
using namespace std;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}
int n, p, k;
int a[MAXN], K[MAXN], prefixMul[MAXN], suffixMul[MAXN];
inline LL qpow(LL a, LL b){
    LL res = 1;
    while(b){
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
inline LL getMul(){
    LL res = 1;
    K[0] = prefixMul[0] = suffixMul[n + 1]= 1;
    for(int i = 1; i <= n; i++){
        res = 1LL * res * a[i] % p;
        K[i] = 1LL * K[i - 1] * k % p; 
        prefixMul[i] = 1LL * prefixMul[i - 1] * a[i] % p;
    }
    for(int i = n; i >= 1; i --) suffixMul[i] = 1LL * suffixMul[i + 1] * a[i] % p;
    return res;
}
int main(){
    cin >> n >> p >> k;
    for(int i = 1; i <= n; i++) a[i] = read();
    LL mulA = getMul();
    LL invMulA = qpow(mulA, p - 2);
    LL res = 0;
    for(int i = 1; i <= n; i++)
        res = (res + (1LL * prefixMul[i - 1] * suffixMul[i + 1] % p * K[i] % p)) % p;
    cout << res * invMulA % p;
    return 0;
}