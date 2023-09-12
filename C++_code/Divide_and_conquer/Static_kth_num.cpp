#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

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

template<typename T>
int partition(T a[], int l, int r, T x) {
    int p = find(a + l, a + r + 1, x) - a;
    assert(l <= p && p <= r);
    swap(a[p], a[l]); // 交换 x 与 a[l]，x 的下标为 l
    int i = l, j = r + 1;
    while (true) {
        while (a[++i] < x && i < r); 
        while (a[--j] > x);
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    a[l] = a[j], a[j] = x;
    return j;
}

template<typename T>
T select(T a[], int l, int r, int k) {
    if (r - l < 75) return sort(a + l, a + r + 1), a[l + k - 1];
    for (int i = 0, tl, tr; i <= (r - l - 4) / 5; i++) {
        tl = l + 5 * i, tr = l + 5 * i + 4;
        sort(a + tl, a + tr + 1);
        swap(a[tl + 2], a[l + i]);
    }
    T x = select(a, l, l + (r - l - 4) / 5, (r - l - 4) / 10);
    int pivot = partition(a, l, r, x), rnk = pivot - l + 1;
    if (k <= rnk) return select(a, l, pivot, k);
    else return select(a, pivot + 1, r, k - rnk);
}

int a[MAXN];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << select(a, 1, n, k) << endl;;
    return 0;
}