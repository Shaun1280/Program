package LinkList;

import java.util.*;

class ListNode {
    int val;
    ListNode next;

    ListNode(int x) {
        val = x;
        next = null;
    }

    ListNode(int val, ListNode next) {
        this.val = val;
        this.next = next;
    }
};

class Solution {
    public ListNode reverseList(ListNode head) {
        ListNode prev = null, cur = head, tmp = null;
        while (cur != null) {
            tmp = cur.next;
            cur.next = prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }

    public ListNode reverseBetween(ListNode head, int left, int right) {
        int cnt = 0;
        ListNode cur = head, prev = null;
        ListNode l = null, ll = null, tmp;
        while (cur != null) {
            cnt++;
            if (cnt + 1 == left) ll = cur;
            else if (cnt == left) l = cur;

            if (left <= cnt && cnt <= right) {
                tmp = cur.next;
                cur.next = prev;
                prev = cur;
                cur = tmp;

                if (cnt == right) {
                    l.next = cur;
                    if (ll != null) {
                        ll.next = prev;
                        return head;
                    } else return prev;
                }
            } else cur = cur.next;
        }
        return null;
    }
};

public class ReverseList {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n;
        n = sc.nextInt();
        ListNode head = null, cur = null;
        for (int i = 1, tmp; i <= n; i++) {
            tmp = sc.nextInt();
            ListNode newNode = new ListNode(tmp, null);
            if (i == 1) {
                head = newNode; cur = newNode;
            } else {
                cur.next = newNode;
                cur = cur.next;
            }
        }
        
        Solution sln = new Solution();
        // cur = sln.reverseList(head);
        cur = sln.reverseBetween(head, 1, 5);
        while (cur != null) {
            System.out.println(cur.val);
            cur = cur.next;
        }
        sc.close();
    }// end of main
}
