#include <bits/stdc++.h>
//CF570D Tree Requests
using namespace std;
//u子树深度为h的节点的字符能否构成回文串 判断奇偶
#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
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

constexpr int MAXN = 5e5 + 5, MOD = 1e9 + 7;

int n, m, tim;
array<int, MAXN> cnt, sum, hson, fa, sz, res, depth, in, from;
char s[MAXN];
vector<int> G[MAXN];
vector<pair<int, int>> q[MAXN]; //first node, second depth
bitset<26> parity[MAXN]; //occurence parity of 26 characters on depth i

void init(int cur, int f) {
    sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
    in[cur] = ++tim, from[tim] = cur;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        init(to, cur);
        sz[cur] += sz[to];
        if (!hson[cur] || sz[to] > sz[hson[cur]]) hson[cur] = to;
    }
}

void add(int cur) { parity[depth[cur]].flip(s[cur] - 'a'); }

void dsu(int cur, bool keep) {
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[cur]) continue;
        dsu(to, false);
    }
    if (hson[cur]) dsu(hson[cur], true);

    add(cur);
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[cur]) continue;
        for (int j = in[to]; j <= in[to] + sz[to] - 1; j++) add(from[j]);
    }
    for (auto& i : q[cur]) res[i.second] = parity[i.first].count() <= 1;

    if (keep == false) {
        for (int j = in[cur]; j <= in[cur] + sz[cur] - 1; j++)
            add(from[j]);
    }
}

int main() {
    read(n, m);
    for (int i = 2, u; i <= n; i++) {
        read(u);
        G[u].emplace_back(i);
    }
    init(1, 0);
    scanf("%s", s + 1);
    for (int i = 1, v, h; i <= m; i++) {
        read(v, h);
        q[v].emplace_back(h, i);
    }
    dsu(1, true);
    for (int i = 1; i <= m; i++) puts(res[i] ? "Yes" : "No");
    return 0;
}