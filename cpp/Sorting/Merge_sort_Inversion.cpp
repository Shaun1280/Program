#include <bits/stdc++.h>
#define LL long long
const int maxn = 1e5 + 1;
using namespace std;
inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x;
}
LL cnt(0);
inline void Merge(int Left, int mid, int Right, int *Arr, int *temp) {
    int l = Left, Index = Left, r = mid + 1;
    while (l <= mid && r <= Right) {
        if (Arr[l] > Arr[r])
            temp[Index++] = Arr[r++], cnt += (LL)(mid - l + 1);
        else
            temp[Index++] = Arr[l++];
    }
    while (l <= mid) temp[Index++] = Arr[l++];
    while (r <= Right) temp[Index++] = Arr[r++];
    for (int i = Left; i <= Right; i++) Arr[i] = temp[i];
}
inline void Merge_sort(int Left, int Right, int *Arr, int *temp) {
    if (Left < Right) {
        int mid = Left + Right >> 1;
        Merge_sort(Left, mid, Arr, temp);
        Merge_sort(mid + 1, Right, Arr, temp);
        Merge(Left, mid, Right, Arr, temp);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w",stdout);
    static int T, n, Arr[maxn], temp[maxn];
    T = read();
    while (T--) {
        n = read(), cnt = 0;
        for (int i = 0; i < n; i++) Arr[i] = read();
        Merge_sort(0, n - 1, Arr, temp);
        cout << cnt << endl;
    }
    return 0;
}