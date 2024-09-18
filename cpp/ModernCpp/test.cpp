#include <bits/stdc++.h>

using namespace std;

constexpr int N = 505;

vector<vector<int>> dp(N, vector<int>(N, 0));
vector<int> a(N), b(N);
long long suma, sumb;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        suma += a[i];
        sumb += b[i];
    }

    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = dp[i - 1][j];
            for (int s1 = max(0, k - b[i]); s1 <= min(k, a[i]); s1++) {
                dp[i][j] = dp[i][j] | dp[i - 1][(j - s1 + k) % k];
            }
        }
    }

    long long ans{0};
    ans = max(ans, suma / k + sumb / k);
    for (int s1 = 0; s1 <= k; s1++) {
        if (dp[n][s1]) {
            int s2 = k - s1;
            if (s1 <= suma && s2 <= sumb)
                ans = max(ans, (suma - s1) / k + (sumb - s2) / k + 1);
        }
    }
    cout << ans << "\n";
    return 0;
}