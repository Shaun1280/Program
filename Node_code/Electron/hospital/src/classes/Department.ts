const Queue = require("../classes/Queue.js")
const Doctor = require("../classes/Doctor.js")
const Patient = require("../classes/Patient.js")

type Patient = InstanceType<typeof Patient>;
type Doctor = InstanceType<typeof Doctor>;
type Queue = InstanceType<typeof Queue>;

class Department { // 科室
    private doctors: Array<Doctor>; // 科室的 3 个医生
    private queueWaitPatient: Queue; // 科室候诊队列
    private displayedPatient: Array<Patient>; // 显示的病人 6 位
    private id: number; // 1-15 普通科室 16 B超室
    private currentPatientID = 1; // 当前分配病人编号

    constructor(_id: number) {
        this.id = _id;
        this.doctors = new Array<Doctor>(4);
        this.displayedPatient = new Array<Patient>();
        for (let i = 1; i <= 3; i++) this.doctors[i]= new Doctor(i, this.id);
        this.queueWaitPatient = new Queue();
    }

    // 分配科室队列队首病人给医生。
    allocatePatient(): void {
        for (let i = 1; i <= 3; i++) {
            if (this.doctors[i].canAllocateNextNewPatient()) {
                let patient = this.queueWaitPatient.pop();
                if (patient !== undefined) { // 队列不为空
                    this.doctors[i].allocateNextNewPatient(patient);
                }
            }
        }
        this.updateDisplayedPatient(); // 更新显示的病人
    }

    // 科室接收挂号的病人，将其加入候诊队列，并进行病人分配
    enqueWaitPatient(patient: Patient): void {
        this.queueWaitPatient.push(patient);
        this.allocatePatient(); // 分配病人给医生
        this.currentPatientID++;
    }

    // 更新科室显示的病人列表
    updateDisplayedPatient(): void {
        this.displayedPatient.length = 0;
        for (let i = 1; i <= 3; i++) {
            if (this.doctors[i].currentPatient != null)
                this.displayedPatient.push(this.doctors[i].currentPatient);
        }
        for (let i = 1; i <= 3; i++) {
            if (this.doctors[i].nextPatient != null) {
                // 普通科室复诊病人不加入显示列表
                if (this.id != 16 && this.doctors[i].nextPatient.treatmentTime != "") continue;

                this.displayedPatient.push(this.doctors[i].nextPatient);
            }
        }
        let rest = 6 - this.displayedPatient.length;
        this.queueWaitPatient.getFrontK(rest, this.displayedPatient);
    }

    // 返回当前病人编号
    getCurrentPatientID(): number { return this.currentPatientID; }
    // 返回第 i 个医生
    getDoctor(i: number): Doctor { return this.doctors[i]; }
    // 返回需要进行显示的病人列表
    getDisplayedPatient(): Array<Patient> { return this.displayedPatient; }
};

module.exports = Department;
