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

constexpr int MAXN = 3e5 + 5, MOD = 1e9 + 7;

template<int MAXN, int LOG>
struct Trie {
    struct TrieNode {
        TrieNode() { son[0] = son[1] = cnt = 0; }
        int son[2], cnt;
    } trie[MAXN * LOG];
    int root = 0, tot = 0, Xor = 0;

    void insert(int x) {
        if (find(x)) return;
        int cur = root;
        for (int i = LOG - 1; ~i; i--) {
            int tmp = (x >> i) & 1;
            if (!trie[cur].son[tmp]) trie[cur].son[tmp] = ++tot;
            cur = trie[cur].son[tmp];
            trie[cur].cnt++;
        }
    }

    bool find(int x) {
        int cur = root;
        for (int i = LOG - 1; ~i; i--) {
            int tmp = (x >> i) & 1;
            if (!trie[cur].son[tmp]) return false;
            cur = trie[cur].son[tmp];
        }
        return true;
    }

    void updateAll(int x) { Xor ^= x; }

    int mex() {
        int cur = root, res = 0;
        for (int i = LOG - 1; ~i; i--) {
            int tmp = (Xor >> i) & 1;
            if (!trie[cur].son[tmp]) return res;
            if (trie[trie[cur].son[tmp]].cnt == (1 << i))
                tmp ^= 1, res += 1 << i;
            if (!trie[cur].son[tmp]) return res;
            cur = trie[cur].son[tmp];
        }
        return res;
    }

};
Trie<MAXN, 20> trie;

int n, m;

int main() {
    boost;
    cin >> n >> m;
    for (int i = 1, tmp; i <= n; i++) {
        cin >> tmp;
        trie.insert(tmp);
    }
    for (int i = 1, x; i <= m; i++) {
        cin >> x;
        trie.updateAll(x);
        cout << trie.mex() << "\n";
    }
    return 0;
}