#include <bits/stdc++.h>
// https://codeforces.ml/contest/1602/problem/E
// E. Optimal Insertion
// 插入 b 后逆序数最小 b 一定升序
// 分治找最优插入位置
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

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T, typename ...Args>
inline void write(T& x , Args&... args) { write(x), putchar('\n'), write(args...); }

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7;

int n, m;
int a[MAXN], b[MAXN], suf[MAXN], pre[MAXN];
vector<int> before[MAXN];

void divide_and_conquer(int bl, int br, int al, int ar) {
    if (bl > br) return;
    int mid = (bl + br) >> 1, val = b[mid], mn = 1e9, pos = ar;
    pre[al - 1] = 0, suf[ar + 1] = 0;
    for (int i = al; i <= ar; i++) pre[i] = pre[i - 1] + (a[i] > val);
    for (int i = ar; i >= al; i--) { // find the best place for insertion
        suf[i] = suf[i + 1] + (a[i] < val);
        if (pre[i - 1] + suf[i] < mn) mn = pre[i - 1] + suf[i], pos = i;
    }
    before[pos].push_back(b[mid]);
    divide_and_conquer(bl, mid - 1, al, pos);
    divide_and_conquer(mid + 1, br, pos, ar);
}

long long inv;
vector<int> vec, tmp;
void merge(int l, int mid, int r) {
    int i = l, idx = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (vec[i] > vec[j])
            tmp[idx++] = vec[j++], inv += mid - i + 1;
        else tmp[idx++] = vec[i++];
    }
    while (i <= mid) tmp[idx++] = vec[i++];
    while (j <= r) tmp[idx++] = vec[j++];
    for (int i = l; i <= r; i++) vec[i] = tmp[i];
}

void mergeSort(int l, int r) {
    if (l < r) {
        int mid = (l + r) >> 1;
        mergeSort(l, mid);
        mergeSort(mid + 1, r);
        merge(l, mid, r);
    }
}

void solveOne(int ncase) {
    vec.clear(), tmp.clear(), inv = 0;
    read(n, m);
    for (int i = 1; i <= n; i++) read(a[i]);
    a[n + 1] = INT_MAX;
    for (int i = 1; i <= m; i++) read(b[i]);
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= n + 1; i++) before[i].clear();
    divide_and_conquer(1, m, 1, n + 1);
    vec.resize(n + m), tmp.resize(n + m);
    for (int i = 1, tot = 0; i <= n + 1; i++) {
        sort(before[i].begin(), before[i].end());
        for (auto& j : before[i]) vec[tot++] = j;
        if (i <= n) vec[tot++] = a[i];
    }
    mergeSort(0, n + m - 1);
    write(inv), putchar('\n');
}

int main() {
    int testcase = 1;
    read(testcase);
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}