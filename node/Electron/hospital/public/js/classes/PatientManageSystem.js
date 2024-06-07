"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Department = require("../classes/Department.js");
const Patient = require("../classes/Patient.js");
// 就诊管理系统
class PatientManageSystem {
    constructor() {
        this.departments = new Array(17);
        for (let i = 1; i <= 16; i++)
            this.departments[i] = new Department(i);
        this.patientList = new Array();
        this.ultrasoundPatientList = new Array();
    }
    // 添加新病人 参数为病人数组
    patientRegister(patients) {
        for (let i = 0; i < patients.length; i++) {
            let id = patients[i].department < 10 ? "0" + patients[i].department : "" + patients[i].department;
            patients[i].id = id + this.departments[patients[i].department].getCurrentPatientID();
            this.departments[patients[i].department].enqueWaitPatient(patients[i]);
            this.patientList.push(patients[i]);
        }
    }
    // 添加前往 B 超室的病人，需要将病人添加到 16 B 超室，并加入等候病人列表
    ultrasoundPatientRegister(patient) {
        this.departments[16].enqueWaitPatient(patient);
        this.ultrasoundPatientList.push(patient);
    }
    // 重新排序就/候诊病人顺序，正在就诊或检查的排在前面
    reorderTreatingPatient(patient) {
        if (patient == null)
            return;
        if (patient.bTreatmentTime == "") { // 非 B 超室病人
            let pos;
            for (pos = 0; pos < this.patientList.length; pos++) {
                if (this.patientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.patientList.length)
                return;
            this.patientList.splice(pos, 1);
            this.patientList.unshift(patient);
        }
        else {
            let pos;
            for (pos = 0; pos < this.ultrasoundPatientList.length; pos++) {
                if (this.ultrasoundPatientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.ultrasoundPatientList.length)
                return;
            this.ultrasoundPatientList.splice(pos, 1);
            this.ultrasoundPatientList.unshift(patient);
        }
    }
    // 从就/候诊病人列表 删除就诊/检查结束的病人 包括去 B 超室的
    removeLeavingPatient(patient) {
        if (patient == null)
            return;
        if (patient.bTreatmentTime == "") { // 非 B 超室病人
            let pos;
            for (pos = 0; pos < this.patientList.length; pos++) {
                if (this.patientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.patientList.length)
                return;
            this.patientList.splice(pos, 1);
        }
        else {
            let pos;
            for (pos = 0; pos < this.ultrasoundPatientList.length; pos++) {
                if (this.ultrasoundPatientList[pos].id === patient.id) {
                    break;
                }
            }
            if (pos >= this.ultrasoundPatientList.length)
                return;
            this.ultrasoundPatientList.splice(pos, 1);
        }
    }
    // Geters
    getPatientList() { return this.patientList; }
    getUltrasoundPatientList() { return this.ultrasoundPatientList; }
    getDepartment(i) { return this.departments[i]; }
}
;
module.exports = PatientManageSystem;
