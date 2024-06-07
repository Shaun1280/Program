"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Patient = require("../classes/Patient.js");
class Queue {
    constructor() {
        this.data = new Array();
    }
    push(item) {
        this.data.push(item);
    }
    pop() {
        return this.data.shift();
    }
    getFrontK(k, patientArray) {
        for (let i = 0; i < Math.min(k, this.data.length); i++)
            patientArray.push(this.data[i]);
    }
    empty() { return this.data.length == 0; }
    clear() {
        this.data = new Array();
    }
}
;
module.exports = Queue;
