#include <bits/stdc++.h>

using namespace std;
using LL = long long;

constexpr int MAXN = 300;
constexpr LL INF = 1e16;
constexpr LL MOD = 998244353;

int t, n, m;

inline LL qpow(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

LL K[110][110], K2[32][110][110];
LL gauss(int n) {  //求矩阵K的n-1阶顺序主子式
    LL res = 1;
    for (int i = 1; i <= n - 1; i++) {  //枚举主对角线上第i个元素
        for (int j = i + 1; j <= n - 1; j++) {  //枚举剩下的行
            while (K[j][i]) {                   //辗转相除
                int t = K[i][i] / K[j][i];
                for (int k = i; k <= n - 1; k++)  //转为倒三角
                    K[i][k] = (K[i][k] - t * K[j][k] + MOD) % MOD;
                swap(K[i], K[j]);  //交换i、j两行
                res = -res;        //取负
            }
        }
        res = (res * K[i][i]) % MOD;
    }
    return (res + MOD) % MOD;
}

LL gauss2(int n, int bit) {  //求矩阵K的n-1阶顺序主子式
    LL res = 1;
    for (int i = 1; i <= n - 1; i++) {  //枚举主对角线上第i个元素
        for (int j = i + 1; j <= n - 1; j++) {  //枚举剩下的行
            while (K2[bit][j][i]) {                   //辗转相除
                int t = K2[bit][i][i] / K2[bit][j][i];
                for (int k = i; k <= n - 1; k++)  //转为倒三角
                    K2[bit][i][k] = (K2[bit][i][k] - t * K2[bit][j][k] + MOD) % MOD;
                swap(K2[bit][i],K2[bit][j]);  //交换i、j两行
                res = -res;        //取负
            }
        }
        res = (res * K2[bit][i][i]) % MOD;
    }
    return (res + MOD) % MOD;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        memset(K, 0, sizeof(K));
        memset(K2, 0, sizeof(K2));
        cin >> n >> m;
        LL ans = 0;
        for (int i = 1, u, v, w; i <= m; i++) {
            cin >> u >> v >> w;
            for (int j = 0; j < 31; j++) {
                int tmp = (w & (1 << j));
                if (tmp) {
                    K2[j][u][u]++, K2[j][v][v]++;
                    K2[j][u][v]--, K2[j][v][u]--;
                }
            }
            K[u][u]++, K[v][v]++;
            K[u][v]--, K[v][u]--;
        }
        LL fenMu = gauss(n);
        for (int i = 0; i < 31; i++) {
            ans = (ans + ((gauss2(n, i) << i) % MOD)) % MOD;
        }
        cout << ans * qpow(fenMu, MOD - 2) % MOD << "\n";
    }
    return 0;
}