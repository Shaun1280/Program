#include <bits/stdc++.h>
using namespace std;
const int maxn = 103, INF = 0x7f7f7f7f;
int a[maxn], dp[maxn];
int n, ans = -INF;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), dp[i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
    printf_s("%d\n", ans);
    return 0;
}
