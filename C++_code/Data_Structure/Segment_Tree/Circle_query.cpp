#include <bits/stdc++.h>
// 等价于找 logC 个区间，区间包含了点 x
// 线段树维护 right[l] = r，最终要找到 right[l] > r 的所有 l（至多 log 个)
// query 通过 set 查找合法区间 总共 LOG 个
#define int long long 

using namespace std;

constexpr int MAXN = 3e6 + 6;

int t;
int opt[MAXN], x[MAXN], y[MAXN];
pair<int, int> p[MAXN];
set<pair<int, int>> l[MAXN];

int n;
vector<int> vec;
map<int, int> mp;
void disc() {
    sort(vec.begin(), vec.end());
    n = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < n; i++) mp[vec[i]] = i + 1;
}

struct Seg {
    int lson, rson;
    int l, r;
    int mx = INT_MIN;
    int id;
} tr[MAXN << 1];

int tot, root;
int newNode(int& root) { return root = ++tot; }

void update(int root) {
    tr[root].mx = max(tr[tr[root].lson].mx, tr[tr[root].rson].mx);
}

void build(int root, int l, int r) {
    tr[root].l = l, tr[root].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(newNode(tr[root].lson), l, mid);
    build(newNode(tr[root].rson), mid + 1, r);
    update(root);
}

void change(int root, int x, int v) {
    if (tr[root].l == x && x == tr[root].r) {
        tr[root].mx = v;
        return;
    }
    int mid = (tr[root].l + tr[root].r) >> 1;
    if (x <= mid) change(tr[root].lson, x, v);
    else change(tr[root].rson, x, v);
    update(root);
}

set<int> ansl;
void query(int root, int x) {
    if (tr[root].l > x || tr[root].mx < x) return;
    if (tr[root].l == tr[root].r) {
        ansl.insert(tr[root].l);
        return;
    }
    query(tr[root].lson, x);
    query(tr[root].rson, x); 
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> opt[i] >> x[i] >> y[i];
        if (opt[i] == 1) {
            vec.push_back(x[i] + y[i] - 1);
            vec.push_back(x[i] - y[i] + 1);
        } else {
            vec.push_back(x[i]);
        }
    }
    disc();
    build(newNode(root), 1, n);
    // cout << "ok" << endl;
    for (int i = 1; i <= t; i++) {
        if (opt[i] == 1) {
            p[i].first = x[i], p[i].second = y[i];
            int R = mp[x[i] + y[i] - 1];
            int L = mp[x[i] - y[i] + 1];
            l[L].insert({R, i});
            change(root, L, (--l[L].end())->first); // T[l] = R
        } else {
            ansl.clear();
            query(root, mp[x[i]]);
            int ans = -1;
            for (auto& L : ansl) {
                auto itr = l[L].lower_bound({mp[x[i]], 0});
                for (; itr != l[L].end(); ++itr) {
                    int id = itr->second;
                    // cout << id << "id \n";
                    if (1LL * (p[id].first - x[i]) * (p[id].first - x[i]) 
                        + 1LL * (p[id].second - y[i]) * (p[id].second - y[i]) < 1LL * p[id].second * p[id].second) {
                        ans = id;
                    }
                }
            }
            cout << ans << "\n";
            if (ans != -1) {
                int L = mp[p[ans].first - p[ans].second + 1];
                int R = mp[p[ans].first + p[ans].second - 1];
                l[L].erase({R, ans});
                change(root, L, l[L].size() ? (--l[L].end())->first : INT_MIN);
            }
        }
    }
    return 0;
}

/*
8
1 0 12
2 -11 22
1 24 10
1 12 3
2 12 12
2 16 14
1 28 15
2 3 6
*/