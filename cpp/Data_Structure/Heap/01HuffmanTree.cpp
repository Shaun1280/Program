#include <bits/stdc++.h>
//01 haffuman tree n ^ 2 数据结构课程作业
using namespace std;

constexpr int MAXN = 127;

struct HTNode {
    HTNode() = default;
    int weight = 0;
    int parent = -1, lchild = -1, rchild = -1;
} *huffmanTree = nullptr;

string huffmanCode[MAXN], code;
int w[MAXN]; //记录每个字符出现次数;

pair<int, int> select(HTNode* huffmanTree, int* w, int lim) {
    int s1 = -1, s2 = -1, min = 1e9, secondMin = 1e9;
    for (int c = 0; c <= lim; c++) {
        if (!huffmanTree[c].weight || huffmanTree[c].parent != -1) continue;
        if (huffmanTree[c].weight < min) min = huffmanTree[c].weight, s1 = c;
    }
    for (int c = 0; c <= lim; c++) {
        if (!huffmanTree[c].weight || huffmanTree[c].parent != -1 || c == s1) continue;
        if (huffmanTree[c].weight < secondMin) secondMin = huffmanTree[c].weight, s2 = c;
    }
    return make_pair(s1, s2);
}

void huffmanCoding(HTNode*& huffmanTree, string* huffmanCode, int* w, int n) {
    huffmanTree = new HTNode[2 * n - 1];
    for (int c = 0; c < n; c++) huffmanTree[c].weight = w[c];
    /*------------------build huffman tree----------------*/
    for (int c = n + 1, s1 = -1, s2 = -1; c < 2 * n - 1; c++) {
        tie(s1, s2) = select(huffmanTree, w, c - 1);
        if (s2 == -1) break;
        if (s1 > s2) swap(s1, s2);
        huffmanTree[s1].parent = c, huffmanTree[s2].parent = c;
        huffmanTree[c].lchild = s1, huffmanTree[c].rchild = s2;
        huffmanTree[c].weight = huffmanTree[s1].weight + huffmanTree[s2].weight;
    }
    /*-----------------求huffman code----------------*/
    for (int c = 0; c < n; c++) {
        string code;
        for (int tmp = c, f = huffmanTree[tmp].parent; f != -1; tmp = f, f = huffmanTree[f].parent)
            if (huffmanTree[f].lchild == tmp) code += "0";
            else code += "1";
        reverse(code.begin(), code.end());
        huffmanCode[c] = code;
        if (code.size() > 0) cout << (char(c)) << " " << huffmanCode[c] << endl;
    }
}

void inputCode(string& code, int* w) {
    cin >> code;
    for (auto& c : code) w[c]++; //出现次数 + 1
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    inputCode(code, w);
    huffmanCoding(huffmanTree, huffmanCode, w, 127);
    delete huffmanTree, huffmanTree = nullptr;
    return 0;
}