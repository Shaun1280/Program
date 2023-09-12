"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Queue = require("../classes/Queue.js");
const Patient = require("../classes/Patient.js");
const { Notification } = require('electron');
let notification;
class Doctor {
    constructor(_id, _type) {
        this.historyPatientList = new Array();
        this.queueReturnPatient = new Queue();
        this.type = _type;
        this.id = _id;
    }
    canAllocateNextNewPatient() {
        if (this.isBusy() || this.nextPatient != null)
            return false;
        let returnPatient = this.queueReturnPatient.pop();
        if (returnPatient === undefined) {
            return true;
        }
        else {
            // 接收复诊病人 未正式诊断
            this.nextPatient = returnPatient;
            return false;
        }
    }
    // 分配新病人
    allocateNextNewPatient(patient) {
        this.nextPatient = patient;
        if (this.type != 16)
            this.nextPatient.doctorid = this.id;
        else
            this.nextPatient.bDoctorid = this.id;
    }
    treatNextPatient() {
        this.currentPatient = this.nextPatient;
        if (this.nextPatient == null)
            return;
        this.nextPatient = null;
        if (this.currentPatient.treatmentTime === "") { // 普通科室新病人
            this.currentPatient.treatmentTime = this.GetTreatmentTime();
            this.historyPatientList.push(this.currentPatient);
            this.sendNotification();
        }
        else if (this.currentPatient.bTreatmentTime === "") { // B 超室新病人
            this.currentPatient.bTreatmentTime = this.GetTreatmentTime();
            this.historyPatientList.push(this.currentPatient);
            this.sendNotification();
        }
        else { // 复诊病人
            // 不需要额外操作 仅在结束时设置就诊结束时间
        }
    }
    sendNotification() {
        if (notification != undefined)
            notification.close();
        notification = new Notification({
            title: '通知 @',
            body: this.type == 16 ? `@ 请 ${this.currentPatient.id} 号 ` + this.currentPatient.name + ` 到 B 超室 doctor-${this.id} 处进行 B 超检查` : `@ 请 ${this.currentPatient.id} 号 ` + this.currentPatient.name + ` 到 ${this.type} 号科室 doctor-${this.id} 处就诊`,
            silent: false,
            timeoutType: 'default'
        });
        notification.show();
    }
    enqueReturnPatient(patient) {
        this.queueReturnPatient.push(patient);
    }
    done() {
        this.leavePatient = this.currentPatient;
        // 未开 B 超 或者已做过 B 超，诊断完全结束
        if (this.leavePatient.bTag == false)
            this.leavePatient.endTime = this.GetTreatmentTime();
        else if (this.type != 16) {
            // 做过 B 超检查的复诊病人
            if (this.leavePatient.bTreatmentTime != "")
                this.leavePatient.endTime = this.GetTreatmentTime();
        }
        else { // B 超室检查结束
            this.leavePatient.bEndTime = this.GetTreatmentTime();
        }
        this.currentPatient = null;
    }
    setUltraSoundTag() { this.currentPatient.bTag = true; }
    isBusy() { return this.currentPatient != null; }
    getStatus() {
        if (this.currentPatient != null)
            return 2; // 忙碌
        if (this.nextPatient != null)
            return 1; // 病人等候中
        return 0; // 空闲
    }
    getHistoryPatientList() {
        return this.historyPatientList;
    }
    getLeavePatient() { return this.leavePatient; }
    getCurrentPatient() { return this.currentPatient; }
    getNextPatient() { return this.nextPatient; }
    GetTreatmentTime() {
        let now = new Date();
        let year = now.getFullYear();
        let month = now.getMonth() + 1;
        let date = now.getDate();
        let hour = now.getHours();
        let minu = now.getMinutes();
        let sec = now.getSeconds();
        let _time = year + "-" + month + "-" + date + " " + hour + ":" + minu + ":" + sec;
        return _time;
    }
}
;
module.exports = Doctor;
