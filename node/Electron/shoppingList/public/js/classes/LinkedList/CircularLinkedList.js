import { LinkedList } from './LinkedList.js';
import { Node } from './Node.js';
// 继承自普通链表
export class CircularLinkedList extends LinkedList {
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
        const node = new Node(element);
        if (ith == 0) { // insert front
            node.next = this.head;
            this.head = node;
            if (this.tail == null)
                this.tail = node, this.tail.next = this.head;
            this.tail.next = node;
        }
        else {
            while (index != this.cnt) {
                if ((++index) == ith) {
                    const tmp = cur.next;
                    cur.next = node;
                    node.next = tmp;
                    if (cur == this.tail)
                        this.tail = cur.next;
                    break;
                }
                cur = cur.next;
            }
        }
        this.cnt++; // node number plus one
        return 1;
    }
    deleteElement(element) {
        let cur = this.head, prev = this.tail, index = 0;
        while (index != this.cnt) {
            ++index;
            if (cur.element === element) {
                if (prev == this.tail)
                    this.head = cur.next, prev.next = this.head;
                else {
                    if (cur == this.tail)
                        this.tail = prev;
                    prev.next = cur.next;
                }
                cur = null;
                this.cnt--;
                return 1;
            }
            prev = cur;
            cur = cur.next;
        }
        return 0; // element not found
    }
    deleteIth(ith) {
        if (ith <= 0 || ith > this.cnt)
            return -1;
        let cur = this.head, index = 0, prev = null;
        while (cur != null) {
            if ((++index) == ith) {
                if (ith == 1)
                    this.head = cur.next, this.tail.next = this.head;
                else {
                    if (cur == this.tail)
                        this.tail = prev;
                    prev.next = cur.next;
                }
                cur = null;
                this.cnt--; // number of nodes minus 1
                return 1;
            }
            prev = cur;
            cur = cur.next;
        }
        return 0; // shouldn't reach here
    }
    found(element) {
        let cur = this.head;
        let index = 0;
        while (index != this.cnt) {
            index++;
            if (cur.element === element)
                return index;
            cur = cur.next;
        }
        return 0;
    }
    display() {
        let cur = this.head, index = 0;
        let output = "";
        while (index != this.cnt) {
            ++index;
            output = output + cur.element + " ";
            cur = cur.next;
        }
        console.log(output);
    }
    updateGraphicArray(graphicArray) {
        graphicArray.length = 0;
        let cur = this.head, index = 0;
        while (index != this.cnt) {
            ++index;
            graphicArray.push(cur.element.toString());
            cur = cur.next;
        }
    }
}
;
