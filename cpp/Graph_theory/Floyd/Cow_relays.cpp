#include <bits/stdc++.h>

constexpr int MAXN = 2e2 + 2;
// P2886 [USACO07NOV]牛继电器Cow Relays
// https://www.luogu.com.cn/problem/P2886
using namespace std;

struct Matrix {
    int m[MAXN][MAXN];
    inline int* operator[](int i) { return m[i]; }
};

Matrix A, E;
int n, m, st, ed, tot;
vector<int> num;
map<int, int> val;
inline Matrix operator*(Matrix a, Matrix b) { //广义矩阵乘法
    Matrix c;
    memset(c.m, 0x3f, sizeof(c.m));
    for (int k = 1; k <= tot; k++)
        for (int i = 1; i <= tot; i++)
            for (int j = 1; j <= tot; j++)
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    return c;
}

inline Matrix operator^(Matrix a, int b) {
    Matrix ans = a;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m >> st >> ed;
    memset(A.m, 0x3f, sizeof(A.m));
    for (int i = 1, w, u, v; i <= m; i++) {
        cin >> w >> u >> v;
        u = val[u] ? val[u] : (val[u] = ++tot);
        v = val[v] ? val[v] : (val[v] = ++tot);
        A[u][v] = A[v][u] = w;
    }
    Matrix S = A ^ (n - 1);
    cout << S[val[st]][val[ed]];
    return 0;
}