#include <bits/stdc++.h>
const int maxn = 1e3 + 1;
using namespace std;
inline void Q_sort(int n, int *Arr) {
    int Pivot = Arr[0], tmp;
    for (int i = 1; i < n; i++)
        if (Arr[i] < Pivot)
            for (int j = i; j >= 1; j--)
                tmp = Arr[j], Arr[j] = Arr[j - 1], Arr[j - 1] = tmp;
    for (int i = 0; i < n; i++) cout << Arr[i] << " ";
}
int main() {
    static int Arr[maxn], n;
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> Arr[i];
    Q_sort(n, Arr);
    return 0;
}