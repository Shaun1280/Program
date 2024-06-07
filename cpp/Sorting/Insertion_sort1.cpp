#include <bits/stdc++.h>
const int MAXN = 1e3 + 3;
using namespace std;
inline void print(int n, int *Arr) {
    for (int i = 0; i < n; i++) cout << Arr[i] << " ";
    cout << endl;
}
inline void Insertion_sort(int n, int *Arr) {
    static int tmp, j;
    for (int i = 1; i < n; i++) {
        if (Arr[i] < Arr[i - 1]) {
            tmp = Arr[i];
            for (j = i - 1; j >= 0 && tmp < Arr[j]; j--)
                Arr[j + 1] = Arr[j], print(n, Arr);
            Arr[j + 1] = tmp, print(n, Arr);
        }
    }
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, Arr[MAXN];
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> Arr[i];
    Insertion_sort(n, Arr);
    return 0;
}