#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3796 P3796 【模板】AC自动机（加强版）
using namespace std;
//统计每个模式串在文本串中出现次数 并输出出现最多的
constexpr int MAXN = 1.05e4 + 5;

struct Trie {
    static int tot;
    Trie() {
        for (int i = 0; i < 26; i++) son[i] = nullptr;
        fail = nullptr, endTag = 0;
    }
    Trie *son[26], *fail;
    int endTag; //记录是哪一个字符串的结尾
} *root, tree[MAXN];

int cnt[200], n;
string str[200];
char tmp[1000005];

int Trie::tot = 0;
inline Trie* newNode(Trie*& root) {
    return root ? root : root = &tree[Trie::tot++];
}

inline void insert(Trie* root, const string& s, int id) {
    for (auto& c : s) root = newNode(root->son[c - 'a']);
    root->endTag = id;
}

inline void getFail() {
    queue<Trie*> q;
    q.push(root);
    root->fail = root;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (cur->son[i]) { //直接赋 fail->son[i]
                cur->son[i]->fail = (cur == root) ? root : cur->fail->son[i];
                q.push(cur->son[i]);
            } else //fail 的儿子 i 设为 cur 的儿子 i
                cur->son[i] = (cur->fail->son[i] ? cur->fail->son[i] : root);
        }
    }
}

inline void match(const string& s, int res = 0) {
    auto cur = root;
    for (auto& c : s) {
        cur = cur->son[c - 'a'];
        auto tmp = cur;
        while (tmp != root) {
            if (tmp->endTag)
                cnt[tmp->endTag]++, res = max(res, cnt[tmp->endTag]);
            tmp = tmp->fail;
        }
    }
    printf("%d\n", res);
    for (int i = 1; i <= n; i++) 
        if (cnt[i] == res) printf("%s\n", str[i].c_str());
    fflush(stdout);
}

inline void clear() {
    root = nullptr;
    for (int i = 0; i < Trie::tot; i++) {
        tree[i].fail = nullptr, tree[i].endTag = 0;
        for (int j = 0; j < 26; j++)
            tree[i].son[j] = nullptr;
    }
    Trie::tot = 0;
}

int main() {
    while (scanf("%d", &n) && n) {
        for (int i = 1; i <= n; i++)
            scanf("%s", tmp), str[i] = tmp, insert(newNode(root), str[i], i);
        getFail();
        scanf("%s", tmp), str[0] = tmp;
        match(str[0]);
        clear();
        fill(cnt, cnt + n + 1, 0);
    }
    return 0;
}