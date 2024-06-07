import { CircularLinkedList } from "../LinkedList/CircularLinkedList.js";
import { LinkedListGraphicBuilder } from "./LinkedListGraphicBuilder.js";
export class CircularLinkedListGraphicBuilder extends LinkedListGraphicBuilder {
    init() {
        this.linkedList = new CircularLinkedList();
        this.graphicArray = new Array();
        this.arrowArray = new Array();
        this.tailArray = new Array();
        this.changeListName();
        this.initD3Arrow(); // d3 链表箭头图形
        this.addBasicEventListeners();
        this.addIpcRenderListeners();
        this.update();
    }
    display() {
        this.displayListNodes();
        this.displayArrows();
        this.displayTailArrow();
        // 根据内容调整 svg 高度
        const svg = document.querySelector('#sh_circleContainer');
        svg.style.height = `${svg.getBBox().y + svg.getBBox().height + LinkedListGraphicBuilder.radius * 2}`;
    }
    displayTailArrow() {
        this.tailArray.length = 0;
        let width = document.querySelector("#sh_circleContainer").clientWidth;
        let rowNodeNumber = Math.trunc((width - 6 * LinkedListGraphicBuilder.radius) / (4 * LinkedListGraphicBuilder.radius) + 1);
        let columnNumber = Math.trunc((this.graphicArray.length - 1) / rowNodeNumber);
        let rowi = (this.graphicArray.length - 1) % rowNodeNumber;
        if (columnNumber & 1)
            rowi = rowNodeNumber - rowi - 1;
        let stx = 4 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius;
        let sty = 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * columnNumber;
        let rx = 6 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius;
        let lx = LinkedListGraphicBuilder.radius;
        if (this.graphicArray.length != 0) {
            if (columnNumber & 1) {
                this.tailArray.push({ x1: stx - 2 * LinkedListGraphicBuilder.radius, y1: sty, x2: lx, y2: sty });
                this.tailArray.push({ x1: lx, y1: sty, x2: lx, y2: 2 * LinkedListGraphicBuilder.radius });
                this.tailArray.push({ x1: lx, y1: 2 * LinkedListGraphicBuilder.radius, x2: lx * 2, y2: 2 * LinkedListGraphicBuilder.radius });
            }
            else {
                this.tailArray.push({ x1: stx, y1: sty, x2: rx, y2: sty });
                this.tailArray.push({ x1: rx, y1: sty, x2: rx, y2: sty + LinkedListGraphicBuilder.ygap });
                this.tailArray.push({ x1: rx, y1: sty + LinkedListGraphicBuilder.ygap, x2: lx, y2: sty + LinkedListGraphicBuilder.ygap });
                this.tailArray.push({ x1: lx, y1: sty + LinkedListGraphicBuilder.ygap, x2: lx, y2: 2 * LinkedListGraphicBuilder.radius });
                this.tailArray.push({ x1: lx, y1: 2 * LinkedListGraphicBuilder.radius, x2: lx * 2, y2: 2 * LinkedListGraphicBuilder.radius });
            }
        }
        console.log("length " + this.tailArray.length);
        d3.select("#g_tail_arrow")
            .selectAll("line")
            .data(this.tailArray)
            .join((enter) => {
            // append an element matching the selector and set constant attributes
            const line_enter = enter.append("line");
            line_enter
                .attr("x1", (d, i) => d.x1)
                .attr("y1", (d, i) => d.y1)
                .attr("x2", (d, i) => d.x2)
                .attr("y2", (d, i) => d.y2)
                .attr("stroke", "red")
                .attr("stroke-width", 2.5)
                .attr("marker-end", (d, i) => i == this.tailArray.length - 1 ? "url(#arrow)" : "");
            line_enter.attr("id", (d, i) => `tailArrow${i + 1}`);
            return line_enter;
        }, 
        // update existing elements
        (update) => {
            update
                .attr("x1", (d, i) => d.x1)
                .attr("y1", (d, i) => d.y1)
                .attr("x2", (d, i) => d.x2)
                .attr("y2", (d, i) => d.y2)
                .attr("marker-end", (d, i) => i == this.tailArray.length - 1 ? "url(#arrow)" : "");
            update.attr("id", (d, i) => `tailArrow${i + 1}`);
            return update;
        }, (exit) => {
            // exit phase
            return exit.remove();
        });
    }
    changeListName() {
        document.getElementById("ListName").innerHTML = "Circular Linked List";
    }
}
