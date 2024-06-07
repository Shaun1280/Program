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

int n;
int a[MAXN], tmp[MAXN];

void merge(int l, int mid, int r) {
    int _l = l, i = l, _r = mid + 1;
    while (_l <= mid && _r <= r) {
        if (a[_l] > a[_r]) tmp[i++] = a[_r++];
        else tmp[i++] = a[_l++];
    }
    while (_l <= mid) tmp[i++] = a[_l++];
    while (_r <= r) tmp[i++] = a[_r++];
    for (int i = l; i <= r; i++) a[i] = tmp[i];
}

void mergeSort(int l, int r) {
    if (l < r) {
        int mid = (l + r) >> 1;
        mergeSort(l, mid);
        mergeSort(mid + 1, r);
        merge(l, mid, r);
    }
}

void run() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    auto st = clock();
    mergeSort(1, n);
    cout << setw(12) << left;
    if (clock() - st > 10000) cout << ">10000ms";
    else cout << to_string(clock() - st ) + "ms";
}

int main() {
    freopen("../result.txt", "a", stdout);
    cout << setw(16) << left;
    cout << "merge sort:";
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

