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

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7, T = 21;

int n, a[MAXN], delta[T];

void init(int n) {
    int t = log2(n);
    for (int i = 1; i <= t; i++) delta[i] = pow(2, t - i + 1) - 1;
}

void shellInsert(int n, int* a, int gap) {
    for (int i = gap + 1, j; i <= n; i++) {
        if (a[i] < a[i - gap]) {
            a[0] = a[i];
            for (j = i - gap; j > 0 && a[j] > a[0]; j -= gap)
                a[j + gap] = a[j];
            a[j + gap] = a[0];
        }
    }
}

void shell_sort(time_t st, int n, int* a) {
    init(n);
    int t = log2(n);
    for (int i = 1; i <= t; i++)
        shellInsert(n, a, delta[i]);
}

void run() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    auto st = clock();
    shell_sort(st, n, a);
    cout << setw(12) << left;
    if (clock() - st > 10000) cout << ">10000ms";
    else cout << to_string(clock() - st ) + "ms";
}

int main() {
    freopen("../result.txt", "a", stdout);
    cout << setw(16) << left;
    cout << "shell sort:";
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