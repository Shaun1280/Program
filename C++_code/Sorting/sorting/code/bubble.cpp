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

void bubble_sort(time_t st, int n, int* a) {
    for (int i = 1; i <= n; i++) {
        if (clock() - st > 10000) return;
        bool kill = true;
        for (int j = 1; j <= n - i; j++)
            if (a[j] > a[j + 1]) kill = false, swap(a[j], a[j + 1]);
        if (kill) break;
    }
}

void run() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    auto st = clock();
    bubble_sort(st, n, a);
    cout << setw(12) << left;
    if (clock() - st > 10000) cout << ">10000ms";
    else cout << to_string(clock() - st ) + "ms";
}

int main() {
    freopen("../result.txt", "a", stdout);
    cout << setw(16) << left;
    cout << "bubble sort:";
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