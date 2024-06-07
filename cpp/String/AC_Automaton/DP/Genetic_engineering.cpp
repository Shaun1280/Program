#pragma omp parallel for
#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF86C
using namespace std;

constexpr int MOD = 1e9 + 9;

struct Trie {
    int son[4] = {0}, fail = 0, len = 0;
} trie[105];

int n, m, ans, root(1), tot(1), f[200];
int dp[1005][105][13], vis[1005][105][13];
string s;

inline void add(int& a, int b) { a = (a + b) % MOD; }

inline void insert(const string& s) {
    int cur = root;
    for (auto& c : s) {
        if (!trie[cur].son[f[c]]) trie[cur].son[f[c]] = ++tot;
        cur = trie[cur].son[f[c]];
    }
    trie[cur].len = s.size();
}

inline void getFail() {
    queue<int> q;
    q.push(root);
    trie[root].fail = root;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        trie[cur].len = max(trie[cur].len, trie[trie[cur].fail].len);
        for (int i = 0; i < 4; i++) {
            if (trie[cur].son[i]) {
                trie[trie[cur].son[i]].fail =
                    (cur == root) ? root : trie[trie[cur].fail].son[i];
                q.push(trie[cur].son[i]);
            } else
                trie[cur].son[i] = trie[trie[cur].fail].son[i]
                                       ? trie[trie[cur].fail].son[i]
                                       : root;
        }
    }
}
/*设 dp[i][j][k] 表示当前长度为 i，对应 AC 自动机上节点编号为 j，最后一段未匹配的字符
长度为 k 的方案数。
由于每个模式串长度不超过 10，故当 k>10k>10 时无解。
设当前状态为 (i,j,k)，如果 j.son 对应某个模式串的结尾，
且该模式串长度大于等于 k+1，那么可以将最后一段未匹配的消去(要么独立构成一个串，
要么是之前串的后缀)，状态转移至 (i+1,j.son,0)；
否则未匹配字符长度加 1，状态转移至 (i+1,j.son,k+1)。最后答案为 ∑dp[n][node][0]。
*/
inline void DP() {
    queue<tuple<int, int, int>> q;
    dp[0][1][0] = 1;
    q.push(make_tuple(0, 1, 0));
    while (!q.empty()) {
        int len = get<0>(q.front());
        int node = get<1>(q.front());
        int last = get<2>(q.front());
        q.pop();
        if (len == n) {
            if (!last) add(ans, dp[len][node][0]);
            continue;
        }
        vis[len][node][last] = 0;
        for (int i = 0; i < 4; i++) {
            int to = trie[node].son[i];
            int tmp = trie[to].len > last ? 0 : last + 1;
            if (tmp > 10) continue;
            add(dp[len + 1][to][tmp], dp[len][node][last]);
            if (!vis[len + 1][to][tmp]) {
                vis[len + 1][to][tmp] = 1;
                q.push(make_tuple(len + 1, to, tmp));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    f['A'] = 0, f['T'] = 1, f['C'] = 2, f['G'] = 3;
    for (int i = 1; i <= m; i++) cin >> s, insert(s);
    getFail();
    DP();
    cout << ans << endl;
    return 0;
}