package Deque;

import java.util.*;

class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int n = nums.length;
        int pre = nums[0], res = nums[0];
        
        Deque<int[]> queue = new ArrayDeque<>();
        queue.offerLast(new int[]{0, pre});

        for (int i = 1; i < 2 * n; i++) {
            while (!queue.isEmpty() && queue.peekFirst()[0] < i - n) {
                queue.pollFirst();
            }
            pre += nums[i % n];
            res = Math.max(res, pre - queue.peekFirst()[1]);
            while (!queue.isEmpty() && queue.peekLast()[1] >= nums[i % n]) {
                queue.pollLast();
            }
            queue.offer(new int[]{i, pre});
        }

        return res;
    }
}
