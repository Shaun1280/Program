import { DoublyLinkedList } from "../LinkedList/DoublyLinkedList.js";
import { LinkedListGraphicBuilder } from "./LinkedListGraphicBuilder.js";

const electron = require('electron');
const { ipcRenderer } = electron;

export class DoublyLinkedListGraphicBuilder extends LinkedListGraphicBuilder {
    protected linkedList?: DoublyLinkedList<string>;

    init(): void { // 重写 init
        this.linkedList = new DoublyLinkedList<string>();
        this.graphicArray = new Array<string>();
        this.arrowArray = new Array<string>();
        this.runningAnimation = false;
        this.initD3Arrow(); // d3 链表箭头图形
        this.changeListName(); // 修改标题为 Doubly Linked List
        this.addBasicEventListeners();
        this.addIpcRenderListeners();
        this.update();
    }

    // 重写父类的 displayArrows 使显示出的指针变为双向的
    protected displayArrows(): void {
        let rowNodeNumber = 0;
        let width = (<SVGElement>document.querySelector("#sh_circleContainer")).clientWidth;
        rowNodeNumber = Math.trunc((width - 6 * LinkedListGraphicBuilder.radius) / (4 * LinkedListGraphicBuilder.radius) + 1);

        this.arrowArray.length = this.graphicArray.length == 0 ? 0 : this.graphicArray.length - 1;

        let getx1 = (d: string, i: number) => { // 箭头起点 x 坐标
            let rowi = i % rowNodeNumber;
            let columni = Math.trunc(i / rowNodeNumber);
            if (columni & 1) rowi = rowNodeNumber - rowi - 1;
            if (i % rowNodeNumber + 1 == rowNodeNumber) {
                if (!(columni & 1)) {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius;
                } else {
                    return 3 * LinkedListGraphicBuilder.radius;
                }
            } else {
                if (!(columni & 1)) {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.radius;
                } else {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius - LinkedListGraphicBuilder.radius;
                }
            }
        }

        let gety1 = (d: string, i: number) => { // 箭头起点 y 坐标
            let rowi = i % rowNodeNumber;
            let columni = Math.trunc(i / rowNodeNumber);
            if (columni & 1) rowi = rowNodeNumber - rowi - 1;
            if (i % rowNodeNumber + 1 == rowNodeNumber) {
                return 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * columni + LinkedListGraphicBuilder.radius;
            } else {
                return 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * columni;
            }
        }

        let getx2 = (d: string, i: number) => { // 箭头终点 x 坐标
            let rowi = i % rowNodeNumber;
            let columni = Math.trunc(i / rowNodeNumber);
            if (columni & 1) rowi = rowNodeNumber - rowi - 1;
            if (i % rowNodeNumber + 1 == rowNodeNumber) { // 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * Math.trunc(i / rowNodeNumber);
                if (!(columni & 1)) {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius;
                } else {
                    return 3 * LinkedListGraphicBuilder.radius;
                }
            } else {
                if (!(columni & 1)) {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius + 3 * LinkedListGraphicBuilder.radius;
                } else {
                    return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius - 3 * LinkedListGraphicBuilder.radius;
                }
            }
        }

        let gety2 = (d: string, i: number) => {
            let rowi = i % rowNodeNumber;
            let columni = Math.trunc(i / rowNodeNumber);
            if (columni & 1) rowi = rowNodeNumber - rowi - 1;
            if (i % rowNodeNumber + 1 == rowNodeNumber) {
                return 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * (columni + 1) - LinkedListGraphicBuilder.radius;
            } else {
                return 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * columni;
            }
        }

        d3.select("#g_circle_and_arrow")
            .selectAll("line")
            .data(this.arrowArray)
            .join((enter) => {
                // append an element matching the selector and set constant attributes
                const line_enter = enter.append("line");
                line_enter
                    .attr("x1", getx1)
                    .attr("y1", gety1)
                    .attr("x2", getx2)
                    .attr("y2", gety2)
                    .attr("stroke", "red")
                    .attr("stroke-width", 2.5)
                    .attr("marker-end", "url(#arrow)")
                    .attr("marker-start", "url(#revArrow)");
                line_enter.attr("id", (d, i) => `arrow${i + 1}`)
                return line_enter;
            },
                // update existing elements
                (update) => {
                    update
                        .attr("x1", getx1)
                        .attr("y1", gety1)
                        .attr("x2", getx2)
                        .attr("y2", gety2)
                    update.attr("id", (d, i) => `arrow${i + 1}`)
                    return update;
                },
                (exit) => {
                    // exit phase
                    return exit.remove();
                });
    }
    
    // 重写父类的 changeListName
    protected changeListName(): void {
        document.getElementById("ListName").innerHTML = "Doubly Linked List";
    }
};