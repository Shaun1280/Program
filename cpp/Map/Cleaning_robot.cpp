#include <bits/stdc++.h>
// AtCoder Beginner Contest 219 F-Cleaning Robot
// 机器人按照命令 k * S = (L+R+U+D)* 移动，问最后能访问多少点
// 先求出初始 set = {(x1, y1), (x2, y2), ..., (xn, yn)} 以及最后到的位置 (a, b)
// 对于每个 (xi, yi)，找到最小的 di，满足 (xi + di * a, yi + di * b) ∈ set
// ans = sum (min(di, k))
// di 可通过取模分组，排序获得
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

#define int long long

string s;
int k, a(0), b(0);
set<pair<int, int>> st;
map<pair<int, int>, vector<int>> g;

signed main() {
    boost;
    cin >> s >> k;
    st.insert({a, b});
    for (const auto& c : s) {
        if (c == 'L') a--;
        else if (c == 'R') a++;
        else if (c == 'U') b--;
        else b++;
        st.insert({a, b});
    }
    if (a == 0 && b == 0) cout << st.size() << "\n";
    else {
        vector<pair<int, int>> vec;
        if (!a) {
            swap(a, b);
            for (auto& i : st) vec.emplace_back(i.second, i.first);
        } else for (auto& i : st) vec.emplace_back(i.first, i.second);
        for (auto& i : vec) {
            int gi;
            if (a > 0) { // 向下取整 注意正负
                if (i.first >= 0) gi = i.first / a;
                else gi = (i.first % a == 0) ? i.first / a : i.first / a - 1;
            } else {
                if (i.first >= 0) gi = (i.first % a == 0) ? i.first / a : i.first / a - 1;
                else gi = i.first / a;
            }
            
            int si = i.first - gi * a;
            int ti = i.second - gi * b;
            g[{si, ti}].emplace_back(gi);
        }

        int ans(0);
        for (auto& i : g) {
            auto vecp = i.second;
            sort(vecp.begin(), vecp.end());
            vector<int> d(vecp.size(), 1e18);
            for (int i = 0; i < vecp.size(); i++) {
                if (i + 1 < vecp.size()) d[i] = min(d[i], vecp[i + 1] - vecp[i]);
                // if (i > 1) d[i] = min(d[i], vecp[i] - vecp[i - 1]);
                ans += min(d[i], k);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}