#include <bits/stdc++.h>
// The min the time to set a new record
// can back to origin
// G. Great Expectations https://codeforces.ml/gym/103049/problem/G
// 2020-2021 ICPC Northwestern European Regional Programming Contest (NWERC 2020)
using namespace std;

#define debug(x) cout << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 5005, MOD = 1e9 + 7;

int n, r, m;
int t[MAXN], d[MAXN];
double p[MAXN];
double dp[55][MAXN]; // before ith trick, j extra time is added

bool check(double mid) {
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= r - n; j++)
            dp[i][j] = 0;
    for (int i = m; i >= 0; i--) {
        for (int j = 0; j <= r - n - 1; j++) {
            dp[i][j] = p[i] * (dp[i + 1][j] + t[i + 1] - t[i]);
            if (j + d[i] <= r - n - 1) {
                dp[i][j] += (1.0 - p[i]) * min(mid, dp[i + 1][j + d[i]] + t[i + 1] - t[i] + d[i]);
            } else {
                dp[i][j] += (1.0 - p[i]) * mid;
            }
        }
    }
    return dp[0][0] < mid + 1e-10;
}

void solveOne(int ncase) {
    cout << setprecision(10) << fixed;
    cin >> n >> r >> m;
    for (int i = 1; i <= m; i++) cin >> t[i] >> p[i] >> d[i];
    t[m + 1] = n, p[0] = 1;
    double l = 0, r = 1e10;
    for (int i = 1; i <= 500; i++) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << r << "\n";
}

int main() {
    boost;
    int testcase = 1;
    // cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}