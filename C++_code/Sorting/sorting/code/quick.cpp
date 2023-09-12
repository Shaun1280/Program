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

int partition(int* a, int l, int r) {
    int pivot = a[l];
    while (l < r) {
        while (l < r && a[r] >= pivot) --r;
        swap(a[l], a[r]);
        while (l < r && a[l] <= pivot) ++l;
        swap(a[l], a[r]);
    }
    return l;
}

void quick_sort(time_t st, int* a, int l, int r) {
    if (l < r) {
        int pivotloc = partition(a, l, r);
        quick_sort(st, a, l, pivotloc - 1);
        quick_sort(st, a, pivotloc + 1, r);
    }
}

void run() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    auto st = clock();
    quick_sort(st, a, 1, n);
    cout << setw(12) << left;
    if (clock() - st > 10000) cout << ">10000ms";
    else cout << to_string(clock() - st ) + "ms";
}

int main() {
    freopen("../result.txt", "a", stdout);
    cout << setw(16) << left;
    cout << "quick sort:";
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