#include <bits/stdc++.h>
//https://codeforces.ml/contest/1445
using namespace std;
//Team building 可撤销并查集
template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 5e5 + 5, MOD = 1e9 + 7;

int n, m, k;
long long ans;
array<int, MAXN * 2> fa, sz, type, skip;
vector<pair<int, int>> e;
stack<pair<int, int>> s;
map<pair<int, int>, vector<pair<int, int>>> mp;
//
int find(int x) { return fa[x] == x ? x : find(fa[x]); }

void merge(int x, int y) {
    int r1 = find(x), r2 = find(y);
    if (sz[r1] > sz[r2]) swap(r1, r2);
    fa[r1] = r2, sz[r2] += sz[r1];
    s.emplace(r1, r2);
}

void undo() {
    fa[s.top().first] = s.top().first;
    sz[s.top().second] -= sz[s.top().first];
    s.pop();
}
//

int main() {
    read(n, m, k);
    for (int i = 1; i <= n; i++) read(type[i]);
    for (int i = 1; i <= 2 * n; i++) fa[i] = i, sz[i] = 1;
    for (int i = 0, u, v; i < m; i++) {
        read(u, v);
        e.emplace_back(u, v);
    }
    for (auto& i : e) { //枚举边
        int x = i.first, y = i.second;
        if (type[x] == type[y]) {
            int r1 = find(x), r2 = find(y);
            if (r1 != r2) merge(x, y + n), merge(y, x + n);
            else skip[type[x]] = true; //academic group自环不计入答案
        }
    }
    for (auto& i : e) { //枚举边
        int x = i.first, y = i.second;
        if (type[x] == type[y]) continue;
        if (skip[type[x]] || skip[type[y]]) continue;
        if (type[x] > type[y]) swap(x, y);
        mp[{type[x], type[y]}].emplace_back(x, y); //放入{type[x], type[y]}对应的vector
    }
    for (auto& node : mp) {
        int cnt = 0;
        for (auto& i : node.second) {
            int x = i.first, y = i.second;
            int r1 = find(x), r2 = find(y);
            if (r1 != r2) merge(x, y + n), merge(y, x + n), cnt += 2; //合并
            else { //type[x] 和 type[y] 不能分为两个集合， x < y
                ans--;
                break;
            }
        }
        while (cnt--) undo(); //roll back
    }
    int cnt = 0;
    for (int i = 1; i <= k; i++) if (!skip[i]) cnt++;
    ans += 1LL * cnt * (cnt - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}