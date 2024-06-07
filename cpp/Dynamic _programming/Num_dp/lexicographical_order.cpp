#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, std::less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//rb tree
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;
//字典序值
void count(const vector<int>& a, const int& n) {
    if (n == 0) {
        cout << "illegal input\n";
        return;
    }
    vector<long long> dp(n);
    ordered_set s;
    dp[0] = a[0] - 1, s.insert(a[0]);
    for (int i = 1; i < n; i++) {
        s.insert(a[i]);
        dp[i] = dp[i - 1] * (n - i);
        int rnk = s.order_of_key(a[i]) + 1; //<= a[i] 的已出现的数的个数
        //error(i, a[i], rnk);
        dp[i] += a[i] - rnk;
    }
    cout << dp.back() << "\n";
}
//下一个全排列
void nextPermutation(const vector<int>& a, const int& n) { //求下一个全排列 O(n)
    vector<int> tmp;
    tmp.assign(a.begin(), a.end());
    int i = n - 2;
    while (i >= 0 && tmp[i] > tmp[i + 1]) --i; //找到第一个 a[i] < a[i + 1]
    if (i < 0) {
        cout << "No next permutation!\n";
        return;
    }
    int j = n - 1;
    while (tmp[j] < tmp[i]) --j; //找到最小的 a[j] > a[i]
    swap(tmp[i], tmp[j]);
    reverse(tmp.begin() + i + 1, tmp.end()); //反转
    for (auto& i : tmp) cout << i << " ";
    cout << "\n";
}

int main() {
    boost;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    count(a, n);
    nextPermutation(a, n);
    return 0;
}