#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...)                           \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        err(_it, args);                          \
    }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template <typename T>
inline void read(T& x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x), read(args...);
}

template <typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

template <typename T, typename... Args>
inline void write(T& x, Args&... args) {
    write(x), putchar('\n'), write(args...);
}

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

void solveOne(int ncase) {
    int n;
    std::string s, t;
    cin >> n >> s >> t;
    int m = (n >> __builtin_ctz(n));

    using smallBase = std::unordered_map<int, std::bitset<2048>>;
    using largeBase = std::unordered_map<int, std::bitset<1'000'000>>;

    auto add = [&](auto& base, auto& x) {
        for (int bit = m - 1; bit >= 0; --bit) {
            if (x.test(bit)) {
                if (base[bit].none()) {
                    base[bit] = x;
                    return true;
                }
                x ^= base[bit];
            }
        }
        return false;
    };

    auto solve =
        [&](const std::string& str) -> std::variant<largeBase, smallBase> {
        if (m <= 2048) {
            auto base = smallBase();
            for (int i = 0; i < n; i += m) {
                auto x = std::bitset<2048>(str.substr(i, m));
                add(base, x);
            }
            return base;
        } else {
            auto base = largeBase();
            for (int i = 0; i < n; i += m) {
                auto x = std::bitset<1'000'000>(str.substr(i, m));
                add(base, x);
            }
            return base;
        }
    };

    auto bs1 = solve(s), bs2 = solve(t);

    auto checkEqual = [&](auto& b1, auto& b2) {
        if (b1.size() != b2.size()) {
            std::cout << "No\n";
            return;
        }

        for (auto&& [_, bs] : b2) {
            if (add(b1, bs)) {
                std::cout << "No\n";
                return;
            }
        }
        cout << "Yes\n";
    };

    if (m <= 2048) {
        auto b1 = std::get<smallBase>(bs1);
        auto b2 = std::get<smallBase>(bs2);
        checkEqual(b1, b2);
    } else {
        auto b1 = std::get<largeBase>(bs1);
        auto b2 = std::get<largeBase>(bs2);
        checkEqual(b1, b2);
    }
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */