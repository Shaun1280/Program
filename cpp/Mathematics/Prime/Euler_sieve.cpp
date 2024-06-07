#include <bits/stdc++.h>

const int Maxn = 1e7 + 7;

using namespace std;

inline int Euler_sieve(int n, bool *isprime, vector<int> &prime) {
    isprime[0] = false, isprime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) prime.push_back(i);
        for (int j = 0; j < prime.size(); j++) {
            if (i * prime[j] > n) break;
            isprime[i * prime[j]] = false;
            if (!(i % prime[j])) break;
        }
    }
    return prime.size();
}

int main() {
    static int n;
    static bool isprime[Maxn];
    cin >> n;
    vector<int> prime;
    memset(isprime, true, sizeof(isprime));
    cout << Euler_sieve(n, isprime, prime) << endl;
    for (int i = 0; i < prime.size(); i++) cout << prime[i] << " ";
    // cout << prime.back();
    return 0;
}