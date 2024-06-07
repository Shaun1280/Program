#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2831 P2831 愤怒的小鸟
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 18, MOD = 1e9 + 7;
constexpr double EPS = 1e-9;

int tc, n, m, dp[MAXN << 18][2];
array<double, MAXN> x, y;
vector<pair<int, int>> valid[MAXN]; //fist state second count

pair<double, double> getParam(double x1, double y1, double x2, double y2) {
    if (abs(x1 - x2) < EPS) return {-1, 0};
    double a = (y1 * x2 - x1 * y2) / (x1 * x1 * x2 - x2 * x2 * x1);
    double b = (x1 * x1 * y2 - x2 * x2 * y1) / (x1 * x1 * x2 - x2 * x2 * x1);
    return {a, b};
}

void init() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        valid[i].clear();
        valid[i].emplace_back(1 << i, 1);
        for (int j = 0; j < n; j++) { //两点确定一条抛物线
            if (j == i) continue;
            double a, b;
            int tot = 0, tmp = 0;
            tie(a, b) = getParam(x[i], y[i], x[j], y[j]);
            if (a > -EPS) continue; //a 必须 < 0
            for (int k = 0; k < n; k++)
                if (abs(y[k] - a * x[k] * x[k] - b * x[k]) < EPS) {
                    tmp += (1 << k); //抛物线上点的状态
                    tot++;
                }
            valid[i].emplace_back(tmp, tot); // i 所能构成的抛物线
        }
    }
}

void DP() {
    init();
    for (int st = 0; st < (1 << n); st++)
        for (int i = 0; i < n; i++) {
            if ((st & (1 << i))) continue; //已被击杀 不再计算
            for (auto& j : valid[i]) {
                int tmp = j.first, tot = j.second;
                if (tot >= n / 3) {
                    dp[st | tmp][1] = min(dp[st | tmp][1], dp[st][0] + 1);
                    dp[st | tmp][1] = min(dp[st | tmp][1], dp[st][1] + 1);
                } else {
                    dp[st | tmp][0] = min(dp[st | tmp][0], dp[st][0] + 1);
                    dp[st | tmp][1] = min(dp[st | tmp][1], dp[st][1] + 1);
                }
            }
        }
    if (m == 2) cout << dp[(1 << n) - 1][1] << "\n";
    else cout << min(dp[(1 << n) - 1][0], dp[(1 << n) - 1][1]) << "\n";
}

int main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        DP();
    }
    return 0;
}