#pragma GCC optimize(2)
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

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7;

int n, a[MAXN];

void insertion_sort(time_t st, int n, int* a) {
    for (int i = 2, j; i <= n; i++) {
        if (clock() - st > 10000) return;
        if (a[i] < a[i - 1]) {
            a[0] = a[i];
            for (j = i - 1; j > 0 && a[j] > a[0]; j--)
                a[j + 1] = a[j];
            a[j + 1] = a[0];
        }
    }
}

void run() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    auto st = clock();
    insertion_sort(st, n, a);
    cout << setw(12) << left;
    if (clock() - st > 10000) cout << ">10000ms";
    else cout << to_string(clock() - st ) + "ms";
}

int main() {
    freopen("../result.txt", "a", stdout);
    cout << setw(16) << left;
    cout << "insertion sort:";
    for (int tc = 1, cnt = 0; tc <= 8; tc++) {
        cnt++;
        string filename;
        stringstream ss;
        ss << "../data/input", ss << cnt, ss << ".txt";
        ss >> filename;
        freopen(filename.c_str(), "r", stdin);
        run();
    }
    cout << "\n";
    return 0;
}