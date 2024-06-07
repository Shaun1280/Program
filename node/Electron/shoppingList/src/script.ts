import { LinkedListGraphicBuilder } from './classes/Graph/LinkedListGraphicBuilder.js'
import { DoublyLinkedListGraphicBuilder } from './classes/Graph/DoublyLinkedListGraphicBuilder.js'
import { CircularLinkedListGraphicBuilder } from './classes/Graph/CircularLinkedListGraphicBuilder.js'

const electron = require('electron');
const { ipcRenderer } = electron;

let linkedListGraphicBuilder = new LinkedListGraphicBuilder(); // 建立图形界面
linkedListGraphicBuilder.init();

ipcRenderer.removeAllListeners('create:slist');
ipcRenderer.on('create:slist', (e, item) => { // 创建单链表
    linkedListGraphicBuilder = new LinkedListGraphicBuilder();
    linkedListGraphicBuilder.init();
});

ipcRenderer.removeAllListeners('create:dlist');
ipcRenderer.on('create:dlist', (e, item) => { // 创建双向链表
    linkedListGraphicBuilder = new DoublyLinkedListGraphicBuilder();
    linkedListGraphicBuilder.init();
})

ipcRenderer.removeAllListeners('create:clist');
ipcRenderer.on('create:clist', (e, item) => { // 创建循环链表
    linkedListGraphicBuilder = new CircularLinkedListGraphicBuilder();
    linkedListGraphicBuilder.init();
})

ipcRenderer.removeAllListeners('clear');
ipcRenderer.on('clear', (e, item) => { // 清空界面
    linkedListGraphicBuilder.init();
})


