#include <bits/stdc++.h>
//https://atcoder.jp/contests/abc175/tasks/abc175_f
using namespace std;
using LL = long long;
//最小代价构造回文串
constexpr int MAXN = 55;

struct Node {
    Node() = default;
    Node(LL _c, string& _l, string& _r) : c(_c), l(_l), r(_r) {}
    LL c;
    string l, r;
    friend inline bool operator<(const Node& lhs, const Node& rhs) {
        return lhs.c > rhs.c;
    }
};
LL n, cost[MAXN];
string s[MAXN], emps("");

inline bool isPalindrome(const string& tmp) {
    for (int i = 0; i < tmp.size() /2 + 1; i++)
        if (tmp[i] != tmp[tmp.size() - 1 - i]) return false;
    return true;
}
/*@return l, r第一个不同的位置*/
inline int check(string& l, string& r) {
    int i = 0;
    for (; i < min(l.size(), r.size()); i++)
        if (l[i] != r[r.size() - 1 - i]) break;
    l = l.substr(i), r = r.substr(0, r.size() - i);
    return i;
}

priority_queue<Node, vector<Node>> q;
map<string, map<string, bool>> vis;
inline void dijkstra() {
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        if (vis[cur.l][cur.r]) continue; //l, r 访问过
        if (isPalindrome(cur.l) && cur.r.empty()) { //左边是回文
            cout << cur.c << endl;
            return;
        } else if (isPalindrome(cur.r) && cur.l.empty()) { //右边是回文
            cout << cur.c << endl;
            return;
        } else if (cur.l.empty() && cur.r.empty()) { //都是空字符串
            cout << cur.c << endl;
            return;
        } else {
            for (int i = 1; i <= n; i++) {
                Node tmp(cur.c, cur.l, cur.r);
                if (tmp.l.size() >= tmp.r.size()) { //左边比右边长，加到右边
                    tmp.r = s[i] + tmp.r, tmp.c += cost[i];
                    int id = check(tmp.l, tmp.r);
                    if (id && (tmp.l.empty() || tmp.r.empty())) q.push(tmp);
                } else { //左边比右边短，加到左边
                    tmp.l = tmp.l + s[i], tmp.c += cost[i];
                    int id = check(tmp.l, tmp.r);
                    if (id && (tmp.l.empty() || tmp.r.empty())) q.push(tmp);
                }
            }
        }
        vis[cur.l][cur.r] = true;
    }
    cout << -1 << endl;
}

int main () {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> cost[i];
        q.push(Node(cost[i], s[i], emps));
        q.push(Node(cost[i], emps, s[i]));
    }
    dijkstra();
    return 0;
}