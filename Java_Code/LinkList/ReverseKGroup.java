package LinkList;

import java.util.*;

class Solution2 {
    public ListNode reverseKGroup(ListNode head, int k) {
        int tot = 0;
        ListNode prevKtail = null;
        ListNode retHead = null;
        ListNode cur = head;
        while (cur != null) {
            tot++;
            cur = cur.next;
        } // get total ListNode

        cur = head;
        while (tot >= k) {
            ListNode curKtail = null, prev = null;
            for (int i = 1; i <= k; i++) {
                if (i == 1) curKtail = cur;
                if (i == k) {
                    if (retHead == null) retHead = cur;
                    if (prevKtail != null) prevKtail.next = cur;
                    prevKtail = curKtail;
                }
                ListNode tmp = cur.next;
                cur.next = prev;
                prev = cur;
                cur = tmp;
            }
            tot -= k;
        }

        if (tot > 0 && prevKtail != null) prevKtail.next = cur;
        return retHead == null ? head : retHead;
    }
};

public class ReverseKGroup {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, k;
        n = sc.nextInt();
        k = sc.nextInt();
        ListNode head = null, cur = null;
        for (int i = 1, tmp; i <= n; i++) { // build linklist
            tmp = sc.nextInt();
            ListNode newNode = new ListNode(tmp, null);
            if (i == 1) {
                head = newNode; cur = newNode;
            } else {
                cur.next = newNode;
                cur = cur.next;
            }
        }
        
        Solution2 sln = new Solution2();
        cur = sln.reverseKGroup(head, k); // k group reversal
        while (cur != null) {
            System.out.println(cur.val);
            cur = cur.next;
        }
        sc.close();
    }// end of main

}// end of class