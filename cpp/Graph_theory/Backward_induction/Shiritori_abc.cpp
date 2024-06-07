#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc209/tasks/abc209_e
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

int charToInt(int a) {
    if (isupper(a)) return a - 'A' + 26;
    else return a - 'a';
}

int stringToInt(char a, char b, char c) {
    return charToInt(a) * 52 * 52 + charToInt(b) * 52 + charToInt(c);
}

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7, M = 52 * 52 * 52;

int n;
string s;
vector<int> revG[M];
array<int, M> in, ans; // ans = 0 -> lose, 1 -> win, -1 -> draw
array<int, MAXN> u, v;

signed main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        u[i] = stringToInt(s[0], s[1], s[2]);
        v[i] = stringToInt(s[s.size() - 3], s[s.size() - 2], s[s.size() - 1]);
        in[u[i]]++;
        revG[v[i]].push_back(u[i]);
    }
    queue<int> q;
    for (int i = 0; i < M; i++) ans[i] = -1;
    for (int i = 0; i < M; i++) if (!in[i]) ans[i] = 0, q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (const auto& to : revG[cur]) {
            if (ans[to] == -1) {
                in[to]--;
                if (ans[cur] == 0) ans[to] = 1, q.push(to);
                else if (in[to] == 0) {
                    ans[to] = 0;
                    q.push(to);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[v[i]] == -1) cout << "Draw\n";
        else if (ans[v[i]] == 0) cout << "Takahashi\n";
        else cout << "Aoki\n";
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