package DP;

class Solution {
    public int maxSubArray(int[] nums) {
        int n = nums.length;

        int pre = nums[0], res = nums[0];
        for (int i = 1; i < n; i++) {
            // add nums[i], or start from nums[i]
            pre = Math.max(pre + nums[i], nums[i]);
            res = Math.max(res, pre);
        }
        return res;
    }
}

public class Leetcode53MaximumSubarray {

}
