#include <bits/stdc++.h>
/*Twins
*Given an inclusive interval of integers from m to n,
*find the number of pairs of twins prime
1<m<n<1e9 n-m<1e6
*/
const int MAXN = 1e6 + 2;
using namespace std;
static bool isprime[MAXN], isprime_small[MAXN];
vector<int> prime;
inline void Segment_sieve(int L, int R) {
    memset(isprime, true, sizeof(isprime));
    memset(isprime_small, true, sizeof(isprime_small));
    for (int i = 2; i < sqrt(R); i++) {
        if (isprime_small[i]) {
            for (int j = i * 2; j < sqrt(R); j += i)
                // i,sqrtR中素数i的整数倍不是素数
                isprime_small[j] = false;
            for (int j = i * max(2, (L + i - 1) / i) /*比L大的最小整数倍*/;
                 j <= R; j += i)
                // L-R 素数i的整数倍不是素数
                isprime[j - L] = false;
        }
    }
    for (int i = 0; i <= R - L; i++)
        if (isprime[i]) prime.push_back(i + L);
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int m, n, cnt = 0;
    cin >> m >> n;
    Segment_sieve(m, n);
    for (int i = 1; i < prime.size(); i++)
        if (prime[i] - prime[i - 1] == 2) cnt++;
    cout << cnt;
    return 0;
}