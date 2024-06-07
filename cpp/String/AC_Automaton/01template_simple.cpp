#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3808 P3808 【模板】AC自动机（简单版）
using namespace std;

constexpr int MAXN = 1e6 + 6;
//有多少模式串在文本串出现过
struct Trie {
    static int tot;
    Trie() {
        for (int i = 0; i < 26; i++) son[i] = nullptr;
        fail = nullptr, cntEnd = 0;
    }
    Trie *son[26], *fail;
    int cntEnd;
} *root, tree[MAXN];

int Trie::tot = 0;
inline Trie* newNode(Trie*& root) {
    return root ? root : root = &tree[Trie::tot++];
}

inline void insert(Trie* root, const string& s) {
    for (int i = 0; i < s.size(); i++)
        root = newNode(root->son[s[i] - 'a']);
    root->cntEnd++;
}

inline void getFail() {
    queue<Trie*> q;
    q.push(root);
    root->fail = root;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (!cur->son[i]) continue;
            if (cur == root) cur->son[i]->fail = root; //根节点儿子的 fail
            else {
                auto to = cur->fail; //cur->son[i] 的父亲节点的 fail
                while (to != root) {
                    if (to->son[i]) {
                        cur->son[i]->fail = to->son[i];
                        break;
                    }
                    to = to->fail; //继续向上找 fail
                }
                if (to == root) // 直到根节点
                    cur->son[i]->fail = root->son[i] ? root->son[i] : root;
            }
            q.push(cur->son[i]); //
        }
    }
}

inline void match(const string& s, int res = 0) {
    auto cur = root;
    for (int i = 0; i < s.size(); i++) {
        while (!cur->son[s[i] - 'a'] && cur != root) cur = cur->fail;
        cur = cur->son[s[i] - 'a'];
        if (!cur) cur = root;
        auto tmp = cur;
        while (tmp != root) {
            if (tmp->cntEnd != -1) {
                res += tmp->cntEnd;
                tmp->cntEnd = -1;
            } else break;
            tmp = tmp->fail;
        }
    }
    printf("%d\n", res);
}

int n;
string s;
char tmp[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", tmp), s = tmp, insert(newNode(root), s);
    getFail();
    scanf("%s", tmp), s = tmp;
    match(s);
    return 0;
}