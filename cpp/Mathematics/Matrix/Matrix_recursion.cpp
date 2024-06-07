#include <bits/stdc++.h>
typedef long long LL;
const int MAXN = 4;
const LL modd = 1000000007;
// P1939 【模板】矩阵加速（数列）
using namespace std;
int T, n;
struct Matrix {
    LL m[4][4];
};
Matrix A, E, Left;
Matrix operator*(Matrix a, Matrix b) {
    Matrix c;
    memset(c.m, 0, sizeof(c.m));
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                c.m[i][j] = (c.m[i][j] + (a.m[i][k] * b.m[k][j]) % modd) % modd;
    return c;
}
inline Matrix Quick_pow(Matrix a, LL b) {
    Matrix ans = E;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> T;
    /*
    F[i] = F[i-1] * 1 + F[i-2] * 0 + F[i-3]* 1
    F[i-1] = F[i-1] * 1 + F[i-2] * 0 + F[i-3]* 0
    F[i-2] = F[i-1] * 0 + F[i-2] * 1 + F[i-3]* 0
    */
    while (T--) {
        cin >> n;
        A.m[1][1] = 1, A.m[1][2] = 1, A.m[1][3] = 0;
        A.m[2][1] = 0, A.m[2][2] = 0, A.m[2][3] = 1;
        A.m[3][1] = 1, A.m[3][2] = 0, A.m[3][3] = 0;
        Left.m[1][1] = Left.m[1][2] = Left.m[1][3] = 1;
        for (int i = 1; i <= 3; i++) E.m[i][i] = 1;
        if (n <= 3) {
            cout << 1 << endl;
            continue;
        }
        Matrix ans = Left * Quick_pow(A, n - 3);
        cout << ans.m[1][1] << endl;
    }
    return 0;
}