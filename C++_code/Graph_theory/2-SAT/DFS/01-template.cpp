#include <bits/stdc++.h>
// 值为 1 的点 字典序最小 O(nm)
// https://acm.hdu.edu.cn/showproblem.php?pid=1814
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

constexpr int MAXN = 8008, MOD = 1e9 + 7;

int n, m, top;
vector<int> g[MAXN * 2];
array<int, MAXN * 2> mark, stk;

void add(int u, int v) { g[u].emplace_back(v); }

void init() {
    for (int i = 0; i < 2 * n; i++) g[i].clear();
    fill(mark.begin(), mark.end(), 0);
}

bool dfs(int cur) { // 将 current 标记为 true
    if (mark[cur ^ 1]) return false;
    if (mark[cur]) return true;
    mark[cur] = true;
    stk[top++] = cur;
    for (auto& to : g[cur]) if (!dfs(to)) return false;
    return true;
}

bool solve() {
    for (int i = 0; i < 2 * n; i += 2) {
        if (!mark[i] && !mark[i ^ 1]) {
            top = 0;
            if (!dfs(i)) {
                while (top > 0) mark[stk[--top]] = false;
                if (!dfs(i + 1)) return false;
            }
        }
    }
    return true;
}

int main() {
    boost;
    while (cin >> n >> m) {
        init();
        for (int i = 1, a, b; i <= m; i++) {
            cin >> a >> b;
            a--, b--;
            add(a, b ^ 1);  // !a | !b
            add(b, a ^ 1);
        }
        if (!solve()) {
            cout << "NIE\n";
        } else {
            for (int i = 0; i < 2 * n; i++)
                if (mark[i]) cout << i + 1 << "\n";
        }
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */