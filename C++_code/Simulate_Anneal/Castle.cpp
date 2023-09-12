#include <bits/stdc++.h>
//P2538 [SCOI2008]城堡 https://www.luogu.com.cn/problem/P2538
using namespace std;

constexpr int MAXN = 55;
constexpr double DOWN = 0.996;
constexpr double EPSILON = 1e-15;

int n, m, k, ans = 0x3f3f3f3f;
int to[MAXN], haveCastle[MAXN], d[MAXN][MAXN];
vector<int> city;

inline void floyed() { //求出两城堡间的距离
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if(i != j && j != k && i !=k)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

inline int calc(int res = 0) {
    for (int i = 0; i < n; i++) {
        int val(0x3f3f3f3f);
        for (int j = 0; j < n; j++)
            if (haveCastle[j])
                val = min(val, d[i][j]);
        res = max(res, val); //求出相邻城堡距离的最大值 可能不存在相邻的情况 设为inf
    }
    return res;
}

inline void SA() {
    double T = 3000;
    while (T > EPSILON) {
        int rndX = rand() % (n - m), rndY = rand() % (n - m);
        swap(haveCastle[city[rndX]], haveCastle[city[rndY]]); 
        //从一开始不是城堡的城市随机选两个城市交换城堡属性
        int tmp = calc();
        int delta = tmp - ans;
        if (delta < 0) ans = tmp;
        else if (exp(-1.0 * delta / T) * RAND_MAX < rand()) //以一定概率不接受
            swap(haveCastle[city[rndX]], haveCastle[city[rndY]]);
        T *= DOWN;
    }
}

inline void solve() {
    auto st = clock();
    for (int i = 0; i < n; i++)
        if (!haveCastle[i]) city.emplace_back(i);
    for (int i = 0; i < k; i++) haveCastle[city[i]] = true; //先选k个
    ans = calc(); //求出结果初始值
    while ((1.0 * (clock() - st) / CLOCKS_PER_SEC) < 0.66)
        SA();
    cout << ans << endl;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    srand(time(NULL));
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> to[i];
    memset(d, 0x3f, sizeof(d));
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp, d[i][to[i]] = d[to[i]][i] = min(d[i][to[i]], tmp);
        d[i][i] = 0;
    }
    floyed();
    for (int i = 0, tmp; i < m; i++)
        cin >> tmp, haveCastle[tmp] = true;
    solve();
    return 0;
}