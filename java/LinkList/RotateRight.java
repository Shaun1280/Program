package LinkList;

import java.util.*;

class Solution3 {
    public ListNode rotateRight(ListNode head, int k) {
        if (head == null) return head;
        int length = 0;
        ListNode cur = head, end = null;
        while (cur != null) {
            length++;
            if (cur.next == null) {
                end = cur;
                end.next = head;
                break;
            } else cur = cur.next;
        }

        length = length - k % length;
        cur = head;
        for (int i = 0; i < length; i++) {
            cur = cur.next;
            end = end.next;
        }
        end.next = null;
        return cur;
    }
};


public class RotateRight {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, k;
        n = sc.nextInt();
        k = sc.nextInt();
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
        
        Solution3 sln = new Solution3();
        cur = sln.rotateRight(head, k);
        while (cur != null) {
            System.out.println(cur.val);
            cur = cur.next;
        }
        sc.close();
    }// end of main
}
