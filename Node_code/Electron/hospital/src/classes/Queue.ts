const Patient = require("../classes/Patient.js")

type Patient = InstanceType<typeof Patient>;

class Queue {
    private data: Array<Patient>;

    constructor() {
        this.data = new Array<Patient>();
    }

    push(item: Patient): void { // 入队 O(1)
        this.data.push(item);
    }

    pop(): Patient | undefined { // 出队 O(1)
        return this.data.shift();
    }

    getFrontK(k: number, patientArray: any[]) { // 取前 k 个元素
        for (let i = 0; i < Math.min(k, this.data.length); i++)
            patientArray.push(this.data[i]);
    }

    empty(): boolean { return this.data.length == 0; }

    clear(): void {
        this.data= new Array<Patient>();
    }
};

module.exports = Queue;
export {}