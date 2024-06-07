import { LinkedList } from './LinkedList.js';
import { DoublyNode } from './Node.js';
// 继承自单链表
export class DoublyLinkedList extends LinkedList {
    insert(element, ith = this.cnt) {
        let success = 1;
        // ith should not be negative or greater than current node number
        if (ith < 0 || ith > this.cnt)
            return -1;
        // the element should only appear once
        if (this.found(element))
            return 0;
        let cur = this.head;
        let index = 0;
        const node = new DoublyNode(element);
        if (ith == 0) { // insert front
            node.next = this.head;
            if (this.head)
                this.head.prev = node;
            this.head = node;
        }
        else {
            while (cur != null) {
                index++;
                if (index == ith) {
                    node.next = cur.next;
                    if (cur.next)
                        cur.next.prev = node;
                    node.prev = cur;
                    cur.next = node;
                    break;
                }
                cur = cur.next;
            }
        }
        this.cnt++; // node number plus one
        return 1;
    }
    deleteElement(element) {
        let cur = this.head;
        while (cur != null) {
            if (cur.element === element) {
                if (cur.prev == null) { // 表头
                    this.head = cur.next;
                    if (cur.next != null)
                        cur.next.prev = null;
                }
                else {
                    cur.prev.next = cur.next;
                    if (cur.next != null)
                        cur.next.prev = cur.prev;
                }
                cur = null;
                this.cnt--;
                return 1;
            }
            cur = cur.next;
        }
        return 0; // element not found
    }
    deleteIth(ith) {
        if (ith <= 0 || ith > this.cnt)
            return -1;
        let cur = this.head, index = 0;
        while (cur != null) {
            if ((++index) == ith) {
                if (ith == 1) { // 删除头
                    this.head = cur.next;
                    if (cur.next != null)
                        cur.next.prev = null;
                }
                else {
                    cur.prev.next = cur.next;
                    if (cur.next != null)
                        cur.next.prev = cur.prev; // 表尾特判
                }
                cur = null;
                this.cnt--; // number of nodes minus 1
                return 1;
            }
            cur = cur.next;
        }
        return 0; // shouldn't reach here
    }
}
