package LinkList;

import java.util.*;

public class DetectCycle {
    static public ListNode detectCycle(ListNode head) {
        if (head == null || head.next == null)
            return null;
        ListNode slow = head;
        ListNode fast = head.next;
        while (slow != fast) {
            if (fast == null || fast.next == null)
                return null;
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode ptr = head;
        slow = slow.next;
        while (ptr != slow) { // a + b + n * (b + c) = 2 * (a + b) => a = c + (n - 1) * (b + c)
            ptr = ptr.next;
            slow = slow.next;
        }
        return ptr;
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int n, pos;
        n = sc.nextInt();
        pos = sc.nextInt();
        ListNode head = null, cur = null, endNxtNode = null;
        for (int i = 1, tmp; i <= n; i++) {
            tmp = sc.nextInt();
            ListNode tmpNode = new ListNode(tmp);
            if (i == pos + 1)
                endNxtNode = tmpNode;
            if (head == null) {
                head = tmpNode;
                cur = head;
            } else {
                cur.next = tmpNode;
                cur = cur.next;
                if (i == n)
                    cur.next = endNxtNode;
            }
        }

        ListNode result = detectCycle(head);
        if (result != null)
            System.out.println(result.val);
        sc.close();
    }
}
