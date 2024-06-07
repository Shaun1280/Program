#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> s, a(n), p(n), ans;
    for (int i = 0; i < n; i++) cin >> a[i];
    s.push_back(a[0]), p[0] = 0;
    for (int i = 1; i < n; i++)
        if (a[i] > s.back()) s.push_back(a[i]), p[i] = s.size() - 1;
        //如果a[i] > a[i-1],则将 a[i] 放入末尾
        else {
            int pos = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
            // binary_search 大于等于a[i]的最小的数
            s[pos] = a[i];  // change_val
            p[i] = pos;
        }
    
    cout << s.size() << endl; // 最长子序列长度
    ans.resize(s.size());
    int idx = s.size() - 1, pre = 0x7fffffff;
    for (int i = n - 1; ~i; i--) {
        if (p[i] == idx && pre > a[i]) {
            ans[idx--] = a[i];
            pre = a[i];
        }
        if (idx == -1) break;
    }
    for (auto& i : ans) cout << i << " ";
    return 0;
}