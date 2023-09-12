#include<bits/stdc++.h>
typedef long long LL;
const int MAXN = 55;
using namespace std;
//P3746 [六省联考2017]组合数问题 reload 
LL n, p, k, r;
struct Matrix{
    LL m[MAXN][MAXN];
    inline LL* operator [](int i){
        return m[i];
    }
};
Matrix E, F, Left; 
//F[i][j] = F[i - 1][j] + F[i - 1][(j -1 + k)%k] 
inline Matrix operator * (Matrix a, Matrix b){
    Matrix c;
    memset(c.m, 0, sizeof(c.m));
    for(int i = 0; i < k; i++)
        for(int j = 0; j < k; j++)
            for(int s = 0; s < k; s++)
                c[i][j] = (c[i][j] + a[i][s] * b[s][j] % p) % p;
    return c;
}
inline Matrix operator ^ (Matrix a, LL b){
    Matrix ans = E;
    while(b){
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> n >> p >> k >> r;
    Left[0][0] =1; // C[0][0] = 1, C[0][1] = 0, C[0][2] = 0
    for(int j = 0; j < k; j++)
        E[j][j] = 1, F[j][j]++, F[(j - 1 + k) % k][j]++;
    Matrix ans = Left * (F ^ (n * k));
    cout << ans[0][r];
    return 0;
}
    /*
    F[i][0] = F[i-1][0] * 1 + F[i-1][1] * 0 + ...      ... + F[i-1][k-1] * 1
    F[i][1] = F[i-1][0] * 0 + F[i-1][1] * 1 + F[i-1][2] * 1 + F[i-1][k-1] * 0
    ...
    F[i][k-1]=F[i-1][0] * 0 + ...   ...   + F[i-1][k-2]*1 + F[i-1][k-1] * 1
    10...0
    01...0
    01...0
    ......
    00...1
    10...1
    */