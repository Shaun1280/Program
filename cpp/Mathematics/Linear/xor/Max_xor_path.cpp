#include <bits/stdc++.h>
// 求从 1 到 n 的最大异或路径 可重复走一条边
// 求出任意一个从 1 到 n 的简单路径
// dfs 求搜索树与非树边构成的环，将这些环边权的异或值插入线性基；
// 其余环也可以通过这些环作为基异或得到
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 5e4 + 5, MOD = 1e9 + 7;

using int64 = int64_t;

template<typename T, const int LIM>
struct LinearCombination {
    void init() { fill(p, p + LIM + 1, 0); }

    void insert(T x) {
        for (int i = LIM; ~i; i--) {
            if (x >> i) { // x 第 i 位为 1
                if (!p[i]) {
                    p[i] = x;
                    break;
                }
                x ^= p[i];
            }
        }
    }

    // 集合内任意几个元素 xor 的最大值
    T qmax(T x = 0) { // 将线性基从高位向低位扫，若 xor 上当前扫到的 pi 答案变大，就把答案异或上 pi。
        T res(x);
        for (int i = LIM; ~i; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }
    T p[LIM + 1];
};
LinearCombination<int64_t, 63> lc; // 0-63 共 64位

int n, m;
int64 dis[MAXN];
bool vis[MAXN];
vector<pair<int, int64>> g[MAXN];

void dfs(int cur) {
    for (auto& e : g[cur]) {
        int to = e.first;
        int64 w = e.second;
        if (!vis[to]) {
            dis[to] = dis[cur] ^ w;
            vis[to] = true;
            dfs(to);
        } else lc.insert(dis[cur] ^ dis[to] ^ w);
    }
}

int main() {
    boost;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int s, t; int64 d;
        cin >> s >> t >> d;
        g[s].emplace_back(t, d);
        g[t].emplace_back(s, d);
    }
    dfs(1);
    cout << lc.qmax(dis[n]) << "\n";
    return 0;
}