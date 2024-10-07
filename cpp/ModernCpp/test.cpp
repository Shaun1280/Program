#include <bits/stdc++.h>

using namespace std;

class Solution {
  private:
    
    int getPrimes() {

    }
  public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<vector<int>> primes(mx + 1);
        for (int x = 2; x <= mx; ++x) {
            int tmp = x, p = 2;
            while (p * p <= tmp) {
                if (tmp % p == 0) {
                    primes[x].push_back(p);
                    while (tmp % p == 0) {
                        tmp /= p;
                    }
                }
                ++p;
            }
            if (tmp > 1) {
                primes[x].push_back(tmp);
            }
        }
    }
};

int main() {
    Solution sln;
    vector<int> nums = {2, 3, 4};
    vector<long long> queries = {0, 2, 2};
    sln.gcdValues(nums, queries);
    return 0;
}

/*
1
10
1 -1 2 2 3 -3 4 -4 5 -5

*/