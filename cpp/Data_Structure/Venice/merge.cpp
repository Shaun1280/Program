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

template<typename T>
struct VeniceSet {
    void add(T v) { s.insert(v + waterLevel); }

    //bool find(T v) { return s.count(v + waterLevel); }

    void updateAll(T v) { waterLevel -= v; } // all remove v

    int size() { return s.size(); }

    ~VeniceSet() { s.clear(); }

    set<T> s;
    T waterLevel = 0;
};

int n;
VeniceSet<long long> *s[MAXN];
array<long long, MAXN> joy, fa, inc, ans;
vector<int> g[MAXN];

void merge(int cur, int to) {
    if (!s[cur]) s[cur] = s[to];
    else {
        if (s[cur]->size() >= s[to]->size()) {
            for (auto& i : s[to]->s) s[cur]->add(i - s[to]->waterLevel);
        } else {
            for (auto& i : s[cur]->s) s[to]->add(i - s[cur]->waterLevel);
            s[cur] = s[to];
        }
    }
}

void dfs(int cur) {
    if (!g[cur].size()) s[cur] = new VeniceSet<long long>;
    for (auto& to : g[cur]) {
        if (to == fa[cur]) continue;
        dfs(to);
        s[to]->updateAll(inc[cur]); //add inc[cur] to all elements
        merge(cur, to);
    }
    s[cur]->add(joy[cur] + inc[cur]);
    ans[cur] = s[cur]->size();
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(joy[i]);
    for (int i = 1; i <= n; i++) {
        read(fa[i]);
        g[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) read(inc[i]);
    for (int i = 1; i <= n; i++) if (!fa[i]) dfs(i);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}