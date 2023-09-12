#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P5357 【模板】AC自动机（二次加强版）
using namespace std;
//拓扑优化 每个模式串出现次数
constexpr int MAXN = 2e5 + 5;

struct Trie {
    static int tot;
    Trie *son[26], *fail;
    int in, cnt;
    vector<int> endTag;
} *root, tree[MAXN];

int cnt[MAXN], n;
string s[MAXN];

int Trie::tot = 0;
inline Trie* newNode(Trie*& root) {
    return root ? root : root = &tree[Trie::tot++];
}

inline void insert(Trie* cur, const string& s, int id) {
    for (auto& c : s) cur = newNode(cur->son[c - 'a']);
    cur->endTag.push_back(id);
}

inline void getFail() {
    queue<Trie*> q;
    q.push(root);
    root->fail = root;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (cur->son[i]) {
                cur->son[i]->fail = (cur == root ? root : cur->fail->son[i]);
                cur->son[i]->fail->in++;
                q.push(cur->son[i]);
            } else //fail 的儿子 i 设为 cur 的儿子 i
                cur->son[i] = (cur->fail->son[i] ? cur->fail->son[i] : root);
        }
    }
}

inline void match(const string& s) {
    auto cur = root;
    for (auto& c : s)
        cur = cur->son[c - 'a'], cur->cnt++;
}

inline void update() {
    queue<Trie*> q;
    for (int i = 0; i < Trie::tot; i++)
        if (!tree[i].in) q.push(&tree[i]);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto& i : cur->endTag) cnt[i] = cur->cnt;
        auto to = cur->fail;
        if (to != root) {
            to->in--, to->cnt += cur->cnt;
            if (!to->in) q.push(to);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << cnt[i] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i], insert(newNode(root), s[i], i);
    getFail();
    cin >> s[0];
    match(s[0]);
    update();
    return 0;
}