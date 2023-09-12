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
struct VeniceSet {
    void add(T v) { s.insert(v + waterLevel); }

    void remove(T v) { s.erase(s.find(v + waterLevel)); }

    void updateAll(T v) { waterLevel += v; } // all remove v

    T getMin() { return *s.begin() - waterLevel; }

    int size() { return s.size(); }

    multiset<T> s;
    T waterLevel = 0;
};

int n;
array<int, MAXN> v, t;
VeniceSet<long long> s;

int main() {
    boost;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) {
        s.add(v[i]), s.updateAll(t[i]);
        long long total = 1LL * t[i] * s.size();
        while (s.size() && s.getMin() < 0) {
            long long toLow = s.getMin();

            total -= abs(toLow);

            s.remove(toLow);
        }
        cout << total << " "; 
    }
    return 0;
}