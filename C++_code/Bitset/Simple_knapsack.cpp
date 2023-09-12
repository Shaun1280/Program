#include <bits/stdc++.h>

using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 1e3 + 3, MOD = 1e9 + 7;

int n, W;
array<int, MAXN> w;

bitset<1000001> dp;

int main() {
    int n;
    cin >> n >> W;
    for (int i = 1; i <= n; i++) cin >> w[i];
    dp[0] = true;
    for (int i = 1; i <= n; i++) {
        dp |= (dp << w[i]);
    }
    cout << dp[W] << endl;
    return 0;
}