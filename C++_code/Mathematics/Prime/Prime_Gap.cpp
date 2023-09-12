#include <bits/stdc++.h>
/*gap between two successive prime numbers p[i] and p[i+1]
 *nearest P[i]<n && nearest P[i+1]>n
 */
const int MAXN = 1300000;
using namespace std;
bool isprime[MAXN];
vector<int> prime;
inline void Euler_sieve() {
    memset(isprime, true, sizeof(isprime));
    isprime[0] = false, isprime[1] = false;
    for (int i = 2; i < MAXN; i++) {
        if (isprime[i]) prime.push_back(i);
        for (int j = 0; j < prime.size(); j++) {
            if (i * prime[j] > MAXN - 1) break;
            isprime[i * prime[j]] = false;
            if (!(i % prime[j])) break;
        }
    }
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n;
    Euler_sieve();
    while (scanf("%d", &n)) {
        if (!n) break;
        if (isprime[n])
            printf("0\n");
        else {
            int r = lower_bound(prime.begin(), prime.end(), n) - prime.begin();
            printf("%d\n", prime[r] - prime[r - 1]);
        }
    }
    return 0;
}