#include <bits/stdc++.h>

using namespace std;

int main() {
    // vector<int> arr = {10, 5, 2, 6}; // 100 5 100 6
    vector<int> arr = {100, 5, 100, 6};
    int k = 100; // 8

    int n = arr.size();
    int mul = 1;
    long long ans = 0;
    for (int l = 0, r = -1; l < n; ++l) {
        if (r < l) {
            mul *= arr[l];
            r = l + 1;
        }
        // cout << l << " " << r << " " << mul << endl;
        while (r < n && mul * arr[r] < k) {
            mul *= arr[r];
            ++r;
        }
        if (mul < k) {
            ans += (r - l);
        }
        // cout << l << " " << r << " " << mul << endl;
        mul /= arr[l];
    }
    cout << ans << endl;
    return 0;
}