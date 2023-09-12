// 单向链表节点
export class Node<T> {
    constructor(public element: T, public next?: Node<T>) { }
}

// 双向链表节点 继承自 Node<T>
export class DoublyNode<T> extends Node<T> {
    constructor(public element: T, public next?: DoublyNode<T>, public prev?: DoublyNode<T>) {
        super(element, next);
    }
}