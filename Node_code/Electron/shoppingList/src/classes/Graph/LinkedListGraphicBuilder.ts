import { LinkedList } from '../LinkedList/LinkedList.js';

const electron = require('electron');
const { ipcRenderer } = electron;

export class LinkedListGraphicBuilder {
    protected linkedList?: LinkedList<string>;
    protected graphicArray: string[]; // 构造 d3 图形的链表数据 array
    protected arrowArray: string[]; // 构造 d3 箭头的数据
    protected runningAnimation: boolean; // 是否正在执行动画

    static readonly radius = 30; // 圆半径
    static readonly ygap = 120; // 上下层间距

    // 初始化
    init(): void {
        this.linkedList = new LinkedList<string>();
        this.graphicArray = new Array<string>();
        this.arrowArray = new Array<string>();
        this.runningAnimation = false;
        this.clear();
        this.changeListName();
        this.initD3Arrow(); // d3 链表箭头图形
        this.addBasicEventListeners();
        this.addIpcRenderListeners();
        this.update();
    }

    // 在插入、删除时进行更新
    protected update(): void {
        this.linkedList.updateGraphicArray(this.graphicArray);
        this.display();
        this.addAnimation();
        this.updateRightClickListeners();
    }

    // 显示图形
    protected display(): void {
        this.displayListNodes();
        this.displayArrows();

        // 根据内容调整 svg 高度
        const svg = (<SVGAElement>document.querySelector('#sh_circleContainer'));
        svg.style.height = `${svg.getBBox().y + svg.getBBox().height + LinkedListGraphicBuilder.radius * 2}`;
    }

    // 加入箭头定义
    protected initD3Arrow(): void {
        // arrow
        var svg = d3.select("svg");
        var defs = svg.append("defs");
        var arrowMarker = defs.append("marker")
            .attr("id", "arrow")
            .attr("markerUnits", "strokeWidth")
            .attr("markerWidth", "12")
            .attr("markerHeight", "12")
            .attr("viewBox", "0 0 12 12")
            .attr("refX", "9")
            .attr("refY", "6")
            .attr("orient", "auto");

        var revArrowMarker = defs.append("marker")
            .attr("id", "revArrow")
            .attr("markerUnits", "strokeWidth")
            .attr("markerWidth", "12")
            .attr("markerHeight", "12")
            .attr("viewBox", "0 0 12 12")
            .attr("refX", "3")
            .attr("refY", "6")
            .attr("orient", "auto");

        var arrow_path = "M2,2 L10,6 L2,10 L6,6 L2,2";
        arrowMarker.append("path")
            .attr("d", arrow_path)
            .attr("fill", "red")
            .attr("opacity", 0.7);

        arrow_path = "M10,2 L2,6 L10,10 L6,6 L10,2"
        revArrowMarker.append("path")
            .attr("d", arrow_path)
            .attr("fill", "red")
            .attr("opacity", 0.7);
    }

    // 添加表单提交事件监听 并通过 ipcRenderer 传输 dialog 提示
    protected addForm1Listener(): void {
        const form1 = <HTMLFormElement>document.querySelector('#form1');
        if (form1 !== null) { // insert after ith  1 <= ith <= list.size()
            form1.onsubmit = (e) => {
                e.preventDefault();
                const inputElement = <HTMLInputElement>document.querySelector('#item1');
                const number = inputElement.value;

                const inputElement2 = <HTMLInputElement>document.querySelector('#ith');
                const ith = inputElement2.value;

                if (number.length == 0) { // 未输入元素
                    ipcRenderer.send("linkedlist:result", 'Input element should not be empty')
                    return;
                }
                if (this.linkedList.found(number)) { // 元素已插入过
                    ipcRenderer.send('linkedlist:result', 'Input element already exist!');
                    return;
                }

                if (ith.length == 0) { // ith 未填写 默认插入到表尾
                    let sz = this.linkedList.size();
                    if (this.linkedList.size() == 0) { // 链表为空跳过动画直接插入
                        this.linkedList.insert(number), this.update(), this.logArray();
                    }
                    else {
                        if (this.runningAnimation) { // 判断是否已有动画执行
                            ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                            return;
                        } else this.runningAnimation = true;
                        this.linkedlistManipulationAnimation(sz, [sz], () => {
                            this.linkedList.insert(number), this.update(), this.logArray();
                        });
                    }
                } else { // 在给定位置插入元素 并根据插入结果进行提示
                    let nodeId = parseInt(ith);
                    if (isNaN(nodeId) || this.linkedList.validIndex(nodeId) == -1) {
                        ipcRenderer.send('linkedlist:result', 'Invalid input index!');
                        return;
                    }
                    if (this.runningAnimation) { // 判断是否已有动画执行
                        ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                        return;
                    } else this.runningAnimation = true;
                    this.linkedlistManipulationAnimation(nodeId, [nodeId], () => {
                        this.linkedList.insert(number, nodeId), this.update(), this.logArray();
                    });
                }
                form1.reset(); // 清空
            }
        }
    }

    // 添加表单提交事件监听 并通过 ipcRenderer 传输 dialog 提示
    protected addForm4Listener(): void {
        const form4 = <HTMLFormElement>document.querySelector('#form4');
        if (form4 !== null) {
            form4.onsubmit = (e) => {
                e.preventDefault();
                const inputElement = <HTMLInputElement>document.querySelector('#item4');
                const number = inputElement.value;

                const inputElement2 = <HTMLInputElement>document.querySelector('#ith4');
                const ith = inputElement2.value;

                if (number.length == 0) {
                    ipcRenderer.send("linkedlist:result", 'Input element should not be empty');
                    return;
                }
                if (this.linkedList.found(number)) { // 元素已插入过
                    ipcRenderer.send('linkedlist:result', 'Input element already exist!');
                    return;
                }

                if (ith.length == 0) { // ith 未填写 默认插入到表头
                    if (this.linkedList.size() == 0) { // 链表为空跳过动画直接插入
                        this.linkedList.insert(number), this.update(), this.logArray();
                    }
                    else {
                        if (this.runningAnimation) { // 判断是否已有动画执行
                            ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                            return;
                        } else this.runningAnimation = true;
                        this.linkedlistManipulationAnimation(1, [0], () => {
                            this.linkedList.insert(number, 0), this.update(), this.logArray();
                        });
                    }
                } else {
                    let nodeId = parseInt(ith);
                    if (isNaN(nodeId) || this.linkedList.validIndex(nodeId) == -1) {
                        ipcRenderer.send('linkedlist:result', 'Invalid input index!');
                        return;
                    }
                    if (this.runningAnimation) { // 判断是否已有动画执行
                        ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                        return;
                    } else this.runningAnimation = true;
                    this.linkedlistManipulationAnimation(nodeId, [nodeId - 1], () => {
                        this.linkedList.insert(number, nodeId - 1), this.update(), this.logArray();
                    });
                }
                form4.reset();
            }
        }
    }

    // 添加表单提交事件监听 并通过 ipcRenderer 传输 dialog 提示
    protected addForm2Listener(): void {
        const form2 = <HTMLFormElement>document.querySelector('#form2');
        if (form2 !== null) {
            form2.onsubmit = (e) => {
                e.preventDefault();
                const inputElement = <HTMLInputElement>document.querySelector('#item2');
                const inputvalue = inputElement.value;

                if (inputvalue.length == 0) return;

                const nodeId = parseInt(inputvalue);

                if (isNaN(nodeId) || this.linkedList.validIndex(nodeId) == -1) { // 非数字输入一律不合法
                    ipcRenderer.send('linkedlist:result', 'Invalid input index!');
                    return;
                }

                if (this.runningAnimation) { // 判断是否已有动画执行
                    ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                    return;
                } else this.runningAnimation = true;

                this.linkedlistManipulationAnimation(nodeId, [nodeId, nodeId - 1], () => {
                    this.linkedList.deleteIth(nodeId);
                    this.update();
                    this.logArray();
                });
                form2.reset(); // 清空
            }
        }
    }

    // 添加表单提交事件监听 并通过 ipcRenderer 传输 dialog 提示
    protected addForm3Listener(): void {
        const form3 = <HTMLFormElement>document.querySelector('#form3');
        if (form3 !== null) {
            form3.onsubmit = (e) => {
                e.preventDefault();
                const inputElement = <HTMLInputElement>document.querySelector('#item3');
                const element = inputElement.value;

                if (element.length == 0) return;

                if (this.runningAnimation) { // 判断是否已有动画执行
                    ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                    return;
                }

                let nodeId = this.linkedList.found(element);
                if (nodeId == 0) {
                    ipcRenderer.send('linkedlist:result', 'No such element!');
                    return;
                }
                this.runningAnimation = true;

                this.linkedlistManipulationAnimation(nodeId, [nodeId, nodeId - 1], () => {
                    this.linkedList.deleteElement(element);
                    this.update();
                    this.logArray();
                });
                form3.reset(); // 清空
            }
        }
    }

    // 添加各种基本 DOM 事件监听
    protected addBasicEventListeners(): void {
        this.addForm1Listener();
        this.addForm4Listener();
        this.addForm2Listener();
        this.addForm3Listener();
        window.onresize = (e) => { this.update(); }
    }

    // 右键点击事件监听 用于传输节点信息给 ipcMain 并显示右键菜单
    protected updateRightClickListeners(): void {
        for (let i = 0; i < this.graphicArray.length; i++) {
            document.getElementById(`node${i + 1}`).onmousedown = (e) => {
                if (e.button == 2) ipcRenderer.send('node:rightClick', i + 1);
            }
        }
    }

    // 右键菜单选项监听 分别为删除事件、元素后插入、元素前插入事件
    protected addIpcRenderListeners(): void {
        ipcRenderer.removeAllListeners('node:delete');
        ipcRenderer.on('node:delete', (e, nodeId) => {
            if (this.runningAnimation) {
                ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                return;
            }
            if (nodeId.length == 0) return;

            this.runningAnimation = true;
            this.linkedlistManipulationAnimation(nodeId, [nodeId, nodeId - 1], () => {
                this.linkedList.deleteIth(nodeId);
                this.update();
                this.logArray();
            });
        })

        ipcRenderer.removeAllListeners('node:insertAfter');
        ipcRenderer.on('node:insertAfter', (e, item, nodeId) => {
            if (this.runningAnimation) {
                ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                return;
            }
            if (item.length == 0) return;
            if (this.linkedList.found(item) != 0) {
                ipcRenderer.send('linkedlist:result', 'Input element already exist!');
                return;
            }

            this.runningAnimation = true;
            this.linkedlistManipulationAnimation(nodeId, [nodeId], () => {
                this.linkedList.insert(item, nodeId);
                this.update();
                this.logArray();
            });
        })

        ipcRenderer.removeAllListeners('node:insertBefore');
        ipcRenderer.on('node:insertBefore', (e, item, nodeId) => {
            if (this.runningAnimation) {
                ipcRenderer.send('linkedlist:result', 'Please try again after animation finished!');
                return;
            }
            if (item.length == 0) return;
            if (this.linkedList.found(item) != 0) {
                ipcRenderer.send('linkedlist:result', 'Input element already exist!');
                return;
            }

            this.runningAnimation = true;
            this.linkedlistManipulationAnimation(nodeId, [nodeId - 1], () => {
                this.linkedList.insert(item, nodeId - 1);
                this.update();
                this.logArray();
            });
        });
    }

    // 添加链表节点颜色渐变动画
    protected addAnimation(): void {
        let beg, rev;

        rev = () => {
            d3.select("svg")
                .selectAll("circle")
                .transition()
                .duration(1500)
                .ease(d3.easeQuadInOut)
                .style("fill-opacity", 0.8)
                .on('end', beg)
        }

        beg = () => {
            d3.select("svg")
                .selectAll("circle")
                .transition()
                .duration(1500)
                .ease(d3.easeQuadInOut)
                .style("fill-opacity", 0.35)
                .on('end', rev)
        }

        beg();
    }

    // 链表增、删时的动画 动画结束后执行回调函数 endCallBack
    protected linkedlistManipulationAnimation(nodeId, arrowIds: number[], endCallBack): void {
        for (let i = 0; i < arrowIds.length; i++) {
            d3.select(`#arrow${arrowIds[i]}`)
            .transition()
            .duration(800)
            .style("opacity", 0);
        }
        

        d3.select(`#node${nodeId}`)
            .selectAll("circle")
            .style("stroke", "rgba(255, 179, 80, 0.884)")
            .style("stroke-width", "5px")
            .style("stroke-opacity", 0.8)

        d3.select(`#node${nodeId}`)
            .transition().duration(800)
            .on('end', () => {
                endCallBack();
                for (let i = 0; i < arrowIds.length; i++) {
                    d3.select(`#arrow${arrowIds[i]}`)
                    .transition()
                    .duration(400)
                    .style("opacity", 0.6);
                }
                d3.select(`#node${nodeId}`).select("circle")
                    .style("stroke", null)
                    .style("stroke-width", null)
                    .style("stroke-opacity", null)
                this.runningAnimation = false;
            });
    }

    // 显示链表节点
    protected displayListNodes(): void {
        let rowNodeNumber = 0;
        let width = (<SVGElement>document.querySelector("#sh_circleContainer")).clientWidth;
        rowNodeNumber = Math.trunc((width - 6 * LinkedListGraphicBuilder.radius) / (4 * LinkedListGraphicBuilder.radius) + 1);
        // console.log(width, rowNodeNumber);

        let getcx = (d: string, i: number) => { // 设置圆心 x 坐标
            let rowi = i % rowNodeNumber;
            let columni = Math.trunc(i / rowNodeNumber);
            if (columni & 1) rowi = rowNodeNumber - rowi - 1;
            return 3 * LinkedListGraphicBuilder.radius + rowi * 4 * LinkedListGraphicBuilder.radius;
        }

        let getcy = (d: string, i: number) => { // 设置圆心 y 坐标
            return 2 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * Math.trunc(i / rowNodeNumber);
        }

        let getText2y = (d: string, i: number) => { // 设置 text2 y 坐标
            return 3 * LinkedListGraphicBuilder.radius + LinkedListGraphicBuilder.ygap * Math.trunc(i / rowNodeNumber) + 10;
        }

        d3.select("#g_circle_and_arrow")
            .selectAll("g")
            .data(this.graphicArray)
            .join((enter) => {
                // append an element matching the selector and set constant attributes
                const g_enter = enter.append("g");
                g_enter.attr("id", (d, i) => `node${i + 1}`)

                // append circles
                g_enter.append("circle")
                    .attr("r", LinkedListGraphicBuilder.radius) // 设置半径
                    .attr("cx", getcx)
                    .attr("cy", getcy)
                    .style("fill", "pink")
                    .style("fill-opacity", 0.7)
                // append relavtive texts
                g_enter.append("text") // 设置节点内容
                    .text((d, i) => `${d}`)
                    .attr("x", getcx)
                    .attr("y", getcy)
                    .classed("circleText", true)
                    .style("text-anchor", "middle");

                g_enter.append("text")
                    .text((d, i) => `No.${i + 1}`)
                    .attr("id", "text2")
                    .attr("x", getcx)
                    .attr("y", getText2y)
                    .classed("circleText", true)
                    .style("text-anchor", "middle");

                return g_enter;
            },
                // update existing elements
                (update) => {
                    update.attr("id", (d, i) => `node${i + 1}`)
                    update.select("circle")
                        .attr("cx", getcx)
                        .attr("cy", getcy)

                    // append relavtive texts
                    update.select("text")
                        .text((d, i) => `${d}`)
                        .attr("x", getcx)
                        .attr("y", getcy)

                    update.select("#text2")
                        .text((d, i) => `No.${i + 1}`)
                        .attr("x", getcx)
                        .attr("y", getText2y);

                    return update;
                },
                (exit) => {
                    // exit phase
                    return exit.remove();
                });
    }

    // 显示链表指针
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
                    .attr("marker-end", "url(#arrow)");
                line_enter.attr("id", (d, i) => `arrow${i + 1}`);
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

    // for debug
    logArray(): void {
        let output: string = "";
        for (let i = 0; i < this.graphicArray.length; i++)
            output = output + this.graphicArray[ i ] + " ";
        console.log("linkedlist array: " + output);
    }

    // 修改链表节点名称
    protected changeListName(): void {
        document.getElementById("ListName").innerHTML = "Single Linked List";
    }

    // 清除 svg
    protected clear(): void {
        document.querySelector('#g_circle_and_arrow').innerHTML = "";
        document.querySelector('#g_tail_arrow').innerHTML = "";
    }
};