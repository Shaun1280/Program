// https://www.luogu.com.cn/blog/user48611/p1962-fei-bo-nei-qie-shuo-lie
#include <bits/stdc++.h>
typedef long long LL;
constexpr int Inf = 0x3f3f3f3f;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

struct Matrix {
    LL m[2][2];
    inline LL* operator[](int i) { return m[i]; }
};
Matrix F, E, Left;
LL M;

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

LL a, b, p, q, n;
int main() {
    std::ios::sync_with_stdio(false);
    cin >> p >> q >> a >> b >> n >> M;
    for (int i = 0; i < 2; i++) E[i][i] = 1;
    F[0][0] = p, F[1][0] = q;
    F[0][1] = 1, F[1][1] = 0;
    Left[0][0] = b, Left[0][1] = a;
    if (n == 0) {
        cout << a;
        return 0;
    }
    if (n == 1) {
        cout << b;
        return 0;
    }
    Matrix ans = Left * (F ^ (n - 2));
    cout << ans[0][0];
    return 0;
}