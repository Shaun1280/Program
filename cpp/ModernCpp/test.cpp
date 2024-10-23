class Solution {
    static int* divisor;

  public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (divisor == nullptr) {
            divisor = new int[1000001];
            for (int i = 1; i <= 1000000; ++i) {
                for (int j = i + i; j <= 1000000; j += i) {
                    divisor[j] = max(divisor[j], i);
                }
            }
        }

        int ans = 0;
        for (int i = n - 2; i >= 0; --i) {
            while (nums[i] > nums[i + 1]) {
                if (divisor[nums[i]] == 1)
                    return -1;
                nums[i] /= divisor[nums[i]];
                ans++;
            }
        }
        return ans;
    }
};
int* Solution::divisor = nullptr;