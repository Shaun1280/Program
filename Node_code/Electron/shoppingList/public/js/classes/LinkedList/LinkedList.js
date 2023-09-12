import { Node } from './Node.js';
export class LinkedList {
    constructor() {
        this.cnt = 0;
    }
    /**
     * @description insert an element after
     * @param {T} element the element to be inserted
     * @param {number} ith insert after the ith node
     * @return {number} status of insertion
     */
    insert(element, ith = this.cnt) {
        let success = 1;
        // ith should not be negative or greater than current node number
        if (ith < 0 || ith > this.cnt)
            return -1;
        // the element should only appear once
        if (this.found(element))
            return 0;
        let cur = this.head; // current node
        let index = 0;
        const node = new Node(element);
        if (ith == 0) { // insert front
            node.next = this.head;
            this.head = node;
        }
        else {
            while (cur != null) {
                if ((++index) == ith) {
                    const tmp = cur.next;
                    cur.next = node;
                    node.next = tmp;
                    break;
                }
                cur = cur.next;
            }
        }
        this.cnt++; // node number plus one
        return 1;
    }
    /**
     *
     */
    deleteElement(element) {
        let cur = this.head, prev = null;
        while (cur != null) {
            if (cur.element === element) {
                if (prev === null)
                    this.head = cur.next;
                else
                    prev.next = cur.next;
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
        if (this.validIndex(ith) == -1)
            return;
        let cur = this.head, index = 0, prev = null;
        while (cur != null) {
            if ((++index) == ith) {
                if (ith == 1)
                    this.head = cur.next;
                else
                    prev.next = cur.next;
                cur = null;
                this.cnt--; // number of nodes minus 1
                return 1;
            }
            prev = cur;
            cur = cur.next;
        }
        return 0; // shouldn't reach here
    }
    /**
     * @description: Return the number of nodes in the linked list
     * @param {T} element The element to be found
     * @return {number} The index(1 based) of the element. 0 by default
     */
    found(element) {
        let cur = this.head;
        let index = 0;
        while (cur != null) {
            index++;
            if (cur.element === element)
                return index;
            cur = cur.next;
        }
        return 0;
    }
    /**
     * @description: return number of nodes in the linked list
     * @return {number} the number of nodes
     */
    size() { return this.cnt; }
    validIndex(ith) {
        if (ith <= 0 || ith > this.cnt)
            return -1;
        return 1;
    }
    display() {
        let cur = this.head;
        let output = "";
        while (cur != null) {
            output = output + cur.element + " ";
            cur = cur.next;
        }
        console.log(output);
    }
    updateGraphicArray(graphicArray) {
        graphicArray.length = 0;
        let cur = this.head;
        while (cur != null) {
            graphicArray.push(cur.element.toString());
            cur = cur.next;
        }
    }
}
;
