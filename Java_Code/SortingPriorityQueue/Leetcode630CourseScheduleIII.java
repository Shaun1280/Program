package SortingPriorityQueue;

import java.util.*;

class Solution {
    public int scheduleCourse(int[][] courses) {
        Arrays.sort(courses, (int[] l, int[] r) -> {
            return l[1] - r[1];
        });

        PriorityQueue<Integer> set = new PriorityQueue<Integer>((a, b) -> b - a);

        int current = 0;
        for (int[] course : courses) {
            if (current + course[0] > course[1]) {
                if (set.isEmpty())
                    continue;
                if (set.peek() > course[0]) {
                    current += course[0] - set.peek();
                    set.poll();
                    set.offer(course[0]);
                }
            } else {
                current += course[0];
                set.offer(course[0]);
            }
        }

        return set.size();
    }
}

public class Leetcode630CourseScheduleIII {

}
