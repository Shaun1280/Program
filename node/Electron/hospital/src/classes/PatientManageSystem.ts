const Department = require("../classes/Department.js")
const Patient = require("../classes/Patient.js")

type Patient = InstanceType<typeof Patient>;
type Department = InstanceType<typeof Department>;

// 就诊管理系统
class PatientManageSystem {
    private departments: Array<Department>; // 16 个科室
    private patientList: Array<Patient>; // 普通科室就/候诊病人列表
    private ultrasoundPatientList: Array<Patient>; // B 超室就/候诊病人列表

    constructor() {
        this.departments = new Array<Department>(17);
        for (let i = 1; i <= 16; i++) this.departments[i] = new Department(i);

        this.patientList = new Array<Patient>();
        this.ultrasoundPatientList = new Array<Patient>();
    }

    // 添加新病人 参数为病人数组
    patientRegister(patients: Patient[]): void {
        for (let i = 0; i < patients.length; i++) {
            let id:string = patients[i].department < 10 ? "0" + patients[i].department : "" + patients[i].department;
            patients[i].id = id + this.departments[patients[i].department].getCurrentPatientID();
            this.departments[patients[i].department].enqueWaitPatient(patients[i]);
            this.patientList.push(patients[i]);
        }
    }

    // 添加前往 B 超室的病人，需要将病人添加到 16 B 超室，并加入等候病人列表
    ultrasoundPatientRegister(patient: Patient): void {
        this.departments[16].enqueWaitPatient(patient);
        this.ultrasoundPatientList.push(patient);
    }

    // 重新排序就/候诊病人顺序，正在就诊或检查的排在前面
    reorderTreatingPatient(patient: Patient): void {
        if (patient == null) return;

        if (patient.bTreatmentTime == "") { // 非 B 超室病人
            let pos: number;
            for (pos = 0; pos < this.patientList.length; pos++) {
                if (this.patientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.patientList.length) return;
            this.patientList.splice(pos, 1);
            this.patientList.unshift(patient);
        } else {
            let pos: number;
            for (pos = 0; pos < this.ultrasoundPatientList.length; pos++) {
                if (this.ultrasoundPatientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.ultrasoundPatientList.length) return;
            this.ultrasoundPatientList.splice(pos, 1);
            this.ultrasoundPatientList.unshift(patient);
        }
    }

    // 从就/候诊病人列表 删除就诊/检查结束的病人 包括去 B 超室的
    removeLeavingPatient(patient: Patient): void { 
        if (patient == null) return;
        if (patient.bTreatmentTime == "") { // 非 B 超室病人
            let pos: number;
            for (pos = 0; pos < this.patientList.length; pos++) {
                if (this.patientList[pos].id === patient.id) {
                    break;
                }
            }

            if (pos >= this.patientList.length) return;
            this.patientList.splice(pos, 1);
        } else {
            let pos: number;
            for (pos = 0; pos < this.ultrasoundPatientList.length; pos++) {
                if (this.ultrasoundPatientList[pos].id === patient.id) {
                    break;
                }
            }

            if (pos >= this.ultrasoundPatientList.length) return;
            this.ultrasoundPatientList.splice(pos, 1);
        }
    }

    // Geters
    getPatientList(): Array<Patient> { return this.patientList; }
    getUltrasoundPatientList(): Array<Patient> { return this.ultrasoundPatientList; }
    getDepartment(i: number): Department { return this.departments[i]; }
};

module.exports = PatientManageSystem;
export {};