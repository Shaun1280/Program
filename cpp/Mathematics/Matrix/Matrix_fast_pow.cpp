#include<bits/stdc++.h>
typedef long long LL; 
const int MAXN = 110;
const LL modd = 1000000007;
using namespace std;
LL n, k;
struct Matrix{
    LL m[MAXN][MAXN];
};
Matrix A, E;
Matrix operator * (Matrix a, Matrix b){
    Matrix c;
    memset(c.m, 0, sizeof(c.m));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <=n; j++)
            for(int k = 1; k <= n; k++)
                c.m[i][j] = (c.m[i][j] + (a.m[i][k] * b.m[k][j]) % modd) % modd;
    return c;
}
inline Matrix Quick_pow(Matrix a, LL b){
    Matrix ans = E;
    while(b){
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> A.m[i][j];
    for(int i = 1; i <= n; i++) E.m[i][i] = 1;
    Matrix ans = Quick_pow(A, k);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << ans.m[i][j] << " ";
        cout << endl;
    }   
    return 0;   
}