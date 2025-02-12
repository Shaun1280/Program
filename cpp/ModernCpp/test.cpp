#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...)                                                         \
    {                                                                          \
        string _s = #args;                                                     \
        replace(_s.begin(), _s.end(), ',', ' ');                               \
        stringstream _ss(_s);                                                  \
        istream_iterator<string> _it(_ss);                                     \
        err(_it, args);                                                        \
    }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template <typename T> inline void read(T& x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch))
        f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template <typename T, typename... Args> inline void read(T& x, Args&... args) {
    read(x), read(args...);
}

template <typename T> inline void write(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

template <typename T, typename... Args> inline void write(T& x, Args&... args) {
    write(x), putchar('\n'), write(args...);
}

constexpr int MAXN = 5e3 + 5, MOD = 998244353;

array<int, MAXN> catlan;

void init() {
    catlan[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 0; j < i; ++j) {
            catlan[i] =
                (catlan[i] + 1LL * catlan[j] * catlan[i - j - 1] % MOD) % MOD;
        }
    }
}

void solveOne(int ncase) {
    int n;
    cin >> n;
    string s(2 * n + 2, '.');
    stack<int> stk;
    s.front() = '(', s.back() = ')';

    cout << catlan[n] << " ";
    for (int i = 0, l, r; i < n; ++i) {
        cin >> l >> r;
        s[l] = '(', s[r] = ')';

        int ans{1};
        for (const auto& c : s) {
            if (c == ')') {
                int cnt{0};
                while (!stk.empty() && stk.top() != '(') {
                    stk.pop();
                    ++cnt;
                }
                ans = 1LL * ans * catlan[cnt / 2] % MOD;
                stk.pop();
            } else {
                stk.push(c);
            }
        }

        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    init();
    for (int i = 1; i <= testcase; i++)
        solveOne(i);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH

5
1 3
0
0 1 -1
2 4
0 100
-100 -50 0 50
2 4
0 1000
-100 -50 0 50
6 6
20 1 27 100 43 42
100 84 1 24 22 77
8 2
564040265 -509489796 469913620 198872582 -400714529 553177666 131159391
-20796763 -1000000000 1000000000

 */