#include <bits/stdc++.h>
typedef long long LL;
const LL M = 1e9 + 7;
using namespace std;
struct Matrix {
    LL m[2][2];
    inline LL* operator[](int i) { return m[i]; }
};
Matrix F, E, Left;
inline Matrix operator*(Matrix a, Matrix b) {
    Matrix c;
    memset(c.m, 0, sizeof(c.m));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int s = 0; s < 2; s++)
                c[i][j] = (c[i][j] + a[i][s] * b[s][j] % M) % M;
    return c;
}
inline Matrix operator^(Matrix a, LL b) {
    Matrix ans = E;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int main() {
    LL n;
    cin >> n;
    for (int i = 0; i < 2; i++) E[i][i] = 1;
    F[0][0] = 1, F[1][0] = 1;
    F[0][1] = 1, F[1][1] = 0;
    Left[0][0] = 1, Left[0][1] = 1;
    if (n <= 2) {
        cout << 1;
        return 0;
    }
    Matrix ans = Left * (F ^ (n - 2));
    cout << ans[0][0];
    return 0;
}