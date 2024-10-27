#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    long long maxScore(vector<int>& nums) {
        if (nums.size() == 1)
            return 1LL * nums[0] * nums[0];
        long long ans = 0;
        for (int skip = -1; skip < (int)nums.size(); skip++) {
            long long _gcd = 0, lcm = 0;
            // cout << "skip: " << skip << endl;
            for (int i = 0; i < nums.size(); i++) {
                if (i == skip)
                    continue;
                if (!_gcd) {
                    _gcd = nums[i];
                    lcm = nums[i];
                } else {
                    _gcd = gcd(_gcd, nums[i]);
                    lcm = lcm * nums[i] / gcd(lcm, nums[i]);
                }
            }
            // cout << _gcd << " " << lcm << endl;
            ans = max(ans, _gcd * lcm);
        }
        return ans;
    }
};

int main() {
    Solution sln;
    vector<int> nums = {2, 4, 8, 16};
    cout << sln.maxScore(nums) << endl;
    return 0;
}