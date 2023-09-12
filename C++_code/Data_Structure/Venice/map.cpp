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

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;
#define int long long

template<typename T>
struct VeniceMap {
    void clear() { m.clear(), waterLevel = 0, sum = 0; }

    void change(T pos, T v) {
        (sum += v - m[pos + waterLevel]) %= MOD;
        (sum += MOD) %= MOD;
        m[pos + waterLevel] = v % MOD;
    }

    T get(T pos) { return m[pos + waterLevel]; }

    void updateAll(T v) { waterLevel -= v; } // all first add v

    int size() { return m.size(); }

    map<T, T> m;
    T waterLevel = 0, sum = 0;
};

int tc, n;
array<int, MAXN> b;
VeniceMap<int> s;

signed main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n;
        int sum(0);
        s.clear();
        for (int i = 1; i <= n; i++) {
            cin >> b[i], sum += b[i];
            if (i == 1) {
                s.change(b[i], 1);
                continue;
            }
            int tmp = s.get(0);
            s.updateAll(b[i]);
            s.change(b[i], tmp); //b[i]为原本0位置的值
            s.change(b[i], s.sum);
        }
        cout << s.sum << "\n";
    }
    return 0;
}