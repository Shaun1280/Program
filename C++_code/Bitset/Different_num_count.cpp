#include <bits/stdc++.h>
//You are given N <= 10^7 numbers, each between 0 and 10^9.
//How many different values appear in the sequence
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

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

bitset<1000000001> visited;

int main() {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        visited[x] = true;
    }
    cout << visited.count();
    //O(size of bitset / 32)
    return 0;
}