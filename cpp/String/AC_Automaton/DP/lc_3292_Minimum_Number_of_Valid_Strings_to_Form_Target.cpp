#include <bits/stdc++.h>

using namespace std;

struct Node {
    std::array<int, 26> son;
    int fail;
    int len;

    Node(int len) : son{}, fail(-1), len(len) {}
};

struct AhoCorasick {
    std::vector<Node> nodes;

    AhoCorasick() : nodes(1, Node(0)) {}

    void put(const std::string& s) {
        int cur = 0;
        for (char x : s) {
            x -= 'a';
            if (nodes[cur].son[x] == 0) {
                nodes[cur].son[x] = nodes.size();
                nodes.emplace_back(nodes[cur].len + 1);
            }
            cur = nodes[cur].son[x];
        }
    }

    void build_fail() {
        nodes[0].fail = 0;
        std::queue<int> q;
        for (int& son : nodes[0].son) {
            if (son == 0) {
                son = 0;
            } else {
                nodes[son].fail = 0;
                q.push(son);
            }
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int& son = nodes[cur].son[i];
                if (son == 0) {
                    son = nodes[nodes[cur].fail].son[i];
                    continue;
                }
                nodes[son].fail = nodes[nodes[cur].fail].son[i];
                q.push(son);
            }
        }
    }
};

class Solution {
  public:
    int minValidStrings(vector<string>& words, string target) {
        AhoCorasick ac;
        for (const auto& word : words) {
            ac.put(word);
        }
        ac.build_fail();

        int n = target.size();
        vector<int> f(n + 1);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';
            cur = ac.nodes[cur].son[x];
            if (cur == 0) {
                return -1;
            }
            f[i + 1] = f[i + 1 - ac.nodes[cur].len] + 1;
        }
        return f[n];
    }
};

/*
Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"

Output: 3

Explanation:

The target string can be formed by concatenating:

Prefix of length 2 of words[1], i.e. "aa".
Prefix of length 3 of words[2], i.e. "bcd".
Prefix of length 3 of words[0], i.e. "abc".
*/
