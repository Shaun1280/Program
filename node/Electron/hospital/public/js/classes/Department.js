const Queue = require("../classes/Queue.js");
const Doctor = require("../classes/Doctor.js");
const Patient = require("../classes/Patient.js");
class Department {
    constructor(_id) {
        this.currentPatientID = 1; // 当前分配病人编号
        this.id = _id;
        this.doctors = new Array(4);
        this.displayedPatient = new Array();
        for (let i = 1; i <= 3; i++)
            this.doctors[i] = new Doctor(i, this.id);
        this.queueWaitPatient = new Queue();
    }
    allocatePatient() {
        for (let i = 1; i <= 3; i++) { // 分配队首病人
            if (this.doctors[i].canAllocateNextNewPatient()) {
                let patient = this.queueWaitPatient.pop();
                if (patient !== undefined) {
                    // console.log(this.id, i);
                    this.doctors[i].allocateNextNewPatient(patient);
                }
            }
        }
        this.updateDisplayedPatient(); // 更新显示的病人
    }
    enqueWaitPatient(patient) {
        this.queueWaitPatient.push(patient);
        this.allocatePatient(); // 分配病人给医生
        this.currentPatientID++;
    }
    updateDisplayedPatient() {
        this.displayedPatient.length = 0;
        for (let i = 1; i <= 3; i++) {
            if (this.doctors[i].currentPatient != null)
                this.displayedPatient.push(this.doctors[i].currentPatient);
        }
        for (let i = 1; i <= 3; i++) {
            if (this.doctors[i].nextPatient != null) {
                // 普通科室复诊病人不加入显示列表
                if (this.id != 16 && this.doctors[i].nextPatient.treatmentTime != "")
                    continue;
                this.displayedPatient.push(this.doctors[i].nextPatient);
            }
        }
        let rest = 6 - this.displayedPatient.length;
        this.queueWaitPatient.getFrontK(rest, this.displayedPatient);
    }
    // 返回当前病人编号
    getCurrentPatientID() { return this.currentPatientID; }
    getDoctor(i) { return this.doctors[i]; }
    getDisplayedPatient() { return this.displayedPatient; }
}
;
module.exports = Department;
